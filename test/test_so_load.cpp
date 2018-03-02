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

int main(int argc, char* argv[]) {

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
    CvtDevice *pdevice = plugin->getdevice(0);
    CvtSensor *psensor = static_cast<CvtSensor *>(pdevice);
    std::cout << "psensor->getid() : " << psensor->getid() << std::endl;

    return 0;
}


