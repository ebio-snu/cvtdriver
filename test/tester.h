/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file tester.h
 @date 2018-02-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for unit tests of a driver.
 It tests to communicate a sensor node with boost::asio.
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#ifndef _TESTER_
#define _TESTER_

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

class Tester {
private:
    boost::shared_ptr<CvtDriver> *_plugin;
    boost::asio::io_service* _pio;
    boost::asio::deadline_timer _timer;
    int _count;

public:
    Tester(boost::asio::io_service& io, boost::shared_ptr<CvtDriver> *plugin)
        : _timer(io, boost::posix_time::seconds(1)), _count(0) {

        _pio = &io;
        _plugin = plugin;
        _timer.async_wait(boost::bind(&Tester::test, this));
    }

    ~Tester() {
        LOG(INFO) << "Final count is " << _count << std::endl;
    }

    void test();
};

#endif

