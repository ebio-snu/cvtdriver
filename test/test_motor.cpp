/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file test_motor.cpp
 @date 2018-03-20, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for unit tests of a driver.
 It makes all motor to open 10%.
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
#include "tester.h"

#define MAXWAIT     5

int _count = 0;
int _updated = 0;
int _tolerate = 0;
int _numact = 0;


int order (boost::shared_ptr<stdcvt::CvtDriver> plugin) {
    int i, n;
    CvtDevice *pdevice;
    CvtMotor *pmotor;

    for (i = n = 0; (pdevice = (plugin)->getdevice(i)) != nullptr; i++) {
        if ((pdevice->getspec ())->getgrouptype() == DG_MOTOR) {
            pmotor = dynamic_cast<CvtMotor *>(pdevice);
            if (pmotor != nullptr) {
                CvtDeviceSpec *pspec = pdevice->getspec ();
                CvtRatioCommand cmd(1, pspec, true, 0.1);
                LOG(INFO) << "before : " << pmotor->tostring();
                pmotor->order (&cmd);
                LOG(INFO) << "after: " << pmotor->tostring();
                n++;
            }
        }
    }

    return n;
}

int check (boost::shared_ptr<stdcvt::CvtDriver> plugin) {
    int i, n;
    CvtDevice *pdevice;
    CvtMotor *pmotor;

    for (i = n = 0; (pdevice = (plugin)->getdevice(i)) != nullptr; i++) {
        if ((pdevice->getspec ())->getgrouptype() == DG_MOTOR) {
            pmotor = dynamic_cast<CvtMotor *>(pdevice);
            if (pmotor != nullptr) {
                LOG(INFO) << "new message : " << pmotor->tostring();
                if ((pmotor->getstatus() == DS_MOT_STOP) &&
                        (pmotor->getcurrent() == 0.1)) {
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

void Tester::test() {
    time_t lastupdated = (*_plugin)->getlastupdated ();

    LOG(INFO) << _count;

    if (_updated == 0 && lastupdated != 0) {
        _numact = order (*_plugin);
        if (_numact > 0) {
            _updated = lastupdated;
            (*_plugin)->postprocess ();
        } else {
            _pio->stop (); // 스위치가 없다면 바로 중지
            return ; 
        }

    } else if (_updated > 0 && lastupdated > _updated) { // message 전송이후
        if (check(*_plugin) < _numact) {
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
    _timer.async_wait(boost::bind(&Tester::test, this));
}


