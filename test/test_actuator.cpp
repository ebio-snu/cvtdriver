/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file test_actuator.cpp
 @date 2018-03-20, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for unit tests of a driver.
 It makes all actuators turn on.
 refer from: https://github.com/ebio-snu/cvtdriver
*/


#include <iostream>

#include <boost/dll/import.hpp> 
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/json_query.hpp>

#include <glog/logging.h>

#include "cvtdriver.h"

using namespace std;
using namespace stdcvt;
using jsoncons::json;
using jsoncons::jsonpath::json_query;

namespace dll = boost::dll;

#define MAXWAIT     3

class timer {
private:
    boost::shared_ptr<CvtDriver> *_plugin;
    boost::asio::io_service* _pio;
    boost::asio::deadline_timer _timer;
    int _count;
    int _updated;
    int _tolerate;  
    int _numact;

public:
    timer(boost::asio::io_service& io, boost::shared_ptr<CvtDriver> *plugin)
        : _timer(io, boost::posix_time::seconds(1))  {
            
        _count = _updated = _tolerate = _numact = 0;
        _pio = &io;
        _plugin = plugin;
        _timer.async_wait(boost::bind(&timer::test, this));
    }

    ~timer() {
        LOG(INFO) << "Final count is " << _count << std::endl;
    }


    int order () {
        int i, n;
        CvtDevice *pdevice;
        CvtActuator *pactuator;

        for (i = n = 0; (pdevice = (*_plugin)->getdevice(i)) != nullptr; i++) {
            if ((pdevice->getspec ())->getgrouptype() == DG_SWITCH) {
                pactuator = dynamic_cast<CvtActuator *>(pdevice);
                if (pactuator != nullptr) {
                    CvtDeviceSpec *pspec = pdevice->getspec ();
                    CvtCommand cmd(1, pspec, true);
                    LOG(INFO) << "before : " << pactuator->tostring();
                    pactuator->order (&cmd);
                    LOG(INFO) << "after: " << pactuator->tostring();
                    n++;
                }
            }
        }

        return n;
    }

    int check () {
        int i, n;
        CvtDevice *pdevice;
        CvtActuator *pactuator;

        for (i = n = 0; (pdevice = (*_plugin)->getdevice(i)) != nullptr; i++) {
            if ((pdevice->getspec ())->getgrouptype() == DG_SWITCH) {
                pactuator = dynamic_cast<CvtActuator *>(pdevice);
                if (pactuator != nullptr) {
                    LOG(INFO) << "new message : " << pactuator->tostring();
                    if (pactuator->getstatus() == DS_SWC_ON) {
                        n++;
                    } else {
                        // not applied
                        LOG(WARNING) << pdevice->getid () << " is not applied yet. ";
                    }
                }
            }
        }
        return n;
    }

    void test() {
        time_t lastupdated = (*_plugin)->getlastupdated ();

        LOG(INFO) << _count;

        if (_updated == 0 && lastupdated != 0) {
            _numact = order ();
            if (_numact > 0) {
                _updated = lastupdated;
                (*_plugin)->postprocess ();
            } else {
                _pio->stop (); // 스위치가 없다면 바로 중지
               return ; 
            }

        } else if (_updated > 0 && lastupdated > _updated) { // message 전송이후
            if (check() < _numact) {
                _tolerate++;
                if (_tolerate > MAXWAIT)
                    throw _tolerate;
                _updated = lastupdated;
                LOG(INFO) << "wait once more.";
            } else {
                _pio->stop (); // 모두 완료
                return ;
            }
        }

        ++_count;
        _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
        _timer.async_wait(boost::bind(&timer::test, this));
    }
};

int main(int argc, char* argv[]) {
    try {
        google::InitGoogleLogging (argv[0]);
        FLAGS_logtostderr = 1;

        boost::asio::io_service io_service;
        boost::shared_ptr<CvtDriver> plugin;
        ifstream is("../conf/cvtdriver.json");
        json config = json::parse(is);

        json temp = config[argv[1]][0]["driver"];
        string driver = "../lib/" + temp.as<string>();
        json tmpoption = config[argv[1]][0]["option"];
        CvtOption option(&tmpoption);
        option.setobject (CVT_OPTION_ASIO_SERVICE, (void *)&io_service);

        LOG(INFO) << "Loading the plugin" << std::endl;

        plugin = dll::import<CvtDriver>(driver, "plugin",                
                        dll::load_mode::append_decorations);

        plugin->initialize (option);

        timer t(io_service, &plugin);

        io_service.run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}


