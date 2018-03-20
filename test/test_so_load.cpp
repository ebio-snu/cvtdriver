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
    CvtDevice *pdevice = plugin->getdevice(0);
    LOG(INFO) << "pdevice->getid() : " << pdevice->getid() << std::endl;

    return 0;
}


