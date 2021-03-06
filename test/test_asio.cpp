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


void Tester::test() {
    LOG(INFO) << _count << std::endl;

    time_t lastupdated = (*_plugin)->getlastupdated();
    if (lastupdated != 0) {
        _pio->stop ();
    } else {
        ++_count;
        _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
        _timer.async_wait(boost::bind(&Tester::test, this));
    }
}

