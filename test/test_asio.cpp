/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file test_asio.cpp
 @date 2018-02-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for unit tests of a driver.
 It tests to communicate a sensor node with boost::asio.
 refer from: https://github.com/ebio-snu/cvtdriver
*/


#include <iostream>

#include <boost/dll/import.hpp> 
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <glog/logging.h>

#include "cvtdriver.h"

using namespace std;
using namespace stdcvt;

namespace dll = boost::dll;

class timer {
private:
    boost::shared_ptr<CvtDriver> *_plugin;
    boost::asio::io_service* _pio;
    boost::asio::deadline_timer _timer;
    int _count;

public:
    timer(boost::asio::io_service& io, boost::shared_ptr<CvtDriver> *plugin)
        : _timer(io, boost::posix_time::seconds(1)), _count(0) {

        _pio = &io;
        _plugin = plugin;
        _timer.async_wait(boost::bind(&timer::print, this));
    }

    ~timer() {
        std::cout << "Final count is " << _count << std::endl;
    }

    void print() {
        std::cout << _count << std::endl;

        CvtDevice *pdevice = (*_plugin)->getdevice(0);
        CvtSensor *psensor = static_cast<CvtSensor *>(pdevice);
        double value = psensor->readobservation();

        std::cout << "psensor->getid() : " << psensor->getid() << std::endl;
        std::cout << "psensor->readobservation() : " << value << std::endl;

        if (value != 0) {
            _pio->stop ();
        } else {
            ++_count;
            _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
            _timer.async_wait(boost::bind(&timer::print, this));
        }
    }

};

int main(int argc, char* argv[]) {
    try {
        google::InitGoogleLogging (argv[0]);

        boost::asio::io_service io_service;
        boost::shared_ptr<CvtDriver> plugin;

        CvtConfig option;
        option.setobject ("boost_io_service", (void *)&io_service);

        std::cout << "Loading the plugin" << std::endl;


        plugin = dll::import<CvtDriver>(  
                argv[1],
                "plugin",                
                dll::load_mode::append_decorations
                );

        plugin->initialize (option);

        timer t(io_service, &plugin);

        io_service.run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


