/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file test_so_load.cpp
 @date 2018-02-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for unit tests of a driver.
 It test to load a shared library.
 refer from: https://github.com/ebio-snu/cvtdriver
*/


#include <iostream>

#include <boost/dll/import.hpp>
#include <boost/asio.hpp>
#include <glog/logging.h>

#include "cvtdriver.h"

using namespace std;
using namespace stdcvt;

namespace dll = boost::dll;

#include "tester.h"

int main(int argc, char* argv[]) {
    google::InitGoogleLogging (argv[0]);
    FLAGS_logtostderr = 1;

    boost::asio::io_service io_service;
    boost::shared_ptr<CvtDriver> plugin;
    ifstream is("../conf/cvtdriver.json");
    json config = json::parse(is);

    json driver = config[argv[1]][0];
    string driverfile = "../lib/" + driver["driver"].as<string>();

    CvtOption option(driver["option"]);
    option.setobject (CVT_OPTION_ASIO_SERVICE, (void *)&io_service);

    CvtDeviceFactory devfac;
    if (driver.has_key("sensors")) {
        devfac.setsensors (driver["sensors"]);
        CvtSensor *psensor = devfac.newsensor(0);
        LOG(INFO) << "sensor: " << psensor->getid ();
    }
    if (driver.has_key("motors")) {
        devfac.setmotors (driver["motors"]);
        CvtMotor *pmotor = devfac.newmotor(0);
        LOG(INFO) << "motor: " << pmotor->getid ();
    }
    if (driver.has_key("switches")) {
        devfac.setswitches (driver["switches"]);
        CvtActuator *pswitch = devfac.newswitch(0);
        LOG(INFO) << "switch: " << pswitch->getid ();
    }

    LOG(INFO) << "Loading the plugin";

    plugin = dll::import<CvtDriver>(driverfile, "plugin",                
                    dll::load_mode::append_decorations);

    plugin->initialize (option, devfac);

    Tester t(io_service, &plugin);
    io_service.run();

    return 0;
}

