/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtdevicefactory.h
 @date 2018-03-20, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for CvtDeviceFactory
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_DEVICE_FACTORY_
#define _CVT_DEVICE_FACTORY_

#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/json_query.hpp>

#include "cvtdevice.h"
#include "cvtcodedic.h"

using namespace std;
using namespace stdcvt;

using jsoncons::json;
using jsoncons::jsonpath::json_query;

namespace stdcvt {

/*
 @brief CvtDeviceFactory는 설정파일에 포함된 장비관련 설정을 전달하기위한 클래스이다.
 장비스펙을 용이하게 전달하기위한 용도로 활용될 수 있다. 
*/
class CvtDeviceFactory {
private:
    json _sensors;        ///< 설정파일에서 센서에 할당된 옵션
    json _motors;         ///< 설정파일에서 모터형 구동기에 할당된 옵션
    json _switches;       ///< 설정파일에서 스위치형 구동기에 할당된 옵션

public:
    /**
     새로운 장비팩토리를 생성한다.
    */
    CvtDeviceFactory() {
    }

    ~CvtDeviceFactory() {
    }

    /**
     센서 생성을 위한 옵션을 추가한다.
     @param sensors 센서를 위한 옵션. json 타입의 포인터.
    */
    void setsensors(json sensors) {
        _sensors = sensors;
    }

    /**
     센서 생성을 위한 옵션을 추가한다.
     @param motors 모터를 위한 옵션. json 타입의 포인터.
    */
    void setmotors(json motors) {
        _motors = motors;
    }

    /**
     센서 생성을 위한 옵션을 추가한다.
     @param switches 스위치를 위한 옵션. json 타입의 포인터.
    */
    void setswitches(json switches) {
        _switches = switches;
    }

    /**
     센서를 생성한다.
     생성된 인스턴스에 대한 해제책임은 사용자에게 있다.
     @param index 0에서 시작하는 인덱스값.
     @return CvtSensor 의 포인터. nullptr 이면 설정없음.
    */
    CvtSensor *newsensor(int index) {
        try  {
            string id = (_sensors)[index]["id"].as<string>();
            devtype_t devtype = (devtype_t)_codedic[_sensors[index]["type"].as<string>()];
            devsec_t section = (devsec_t)_codedic[_sensors[index]["section"].as<string>()];
            devtarget_t target = (devtarget_t)_codedic[_sensors[index]["target"].as<string>()];
            devstat_t devstatus = (devstat_t)_codedic[_sensors[index]["status"].as<string>()];
            obsunit_t unit = (obsunit_t)_codedic[_sensors[index]["unit"].as<string>()];

            return new CvtSensor (id, devtype, section, target, devstatus, unit);
        } catch (...) {
            return nullptr;
        }
    }

    /**
     스위치를 생성한다.
     생성된 인스턴스에 대한 해제책임은 사용자에게 있다.
     @param index 0에서 시작하는 인덱스값.
     @return CvtActuator의 포인터. nullptr 이면 설정없음.
    */
    CvtActuator *newswitch(int index) {
        try  {
            string id = (_switches)[index]["id"].as<string>();
            devtype_t devtype = (devtype_t)_codedic[_switches[index]["type"].as<string>()];
            devsec_t section = (devsec_t)_codedic[_switches[index]["section"].as<string>()];
            devtarget_t target = (devtarget_t)_codedic[_switches[index]["target"].as<string>()];
            devstat_t devstatus = (devstat_t)_codedic[_switches[index]["status"].as<string>()];

            return new CvtActuator (id, devtype, section, target, devstatus);
        } catch (...) {
            return nullptr;
        }
    }

    /**
     모터를 생성한다.
     생성된 인스턴스에 대한 해제책임은 사용자에게 있다.
     @param index 0에서 시작하는 인덱스값.
     @return CvtMotor의 포인터. nullptr 이면 설정없음.
    */
    CvtMotor *newmotor(int index) {
        try  {
            string id = (_motors)[index]["id"].as<string>();
            devtype_t devtype = (devtype_t)_codedic[_motors[index]["type"].as<string>()];
            devsec_t section = (devsec_t)_codedic[_motors[index]["section"].as<string>()];
            devtarget_t target = (devtarget_t)_codedic[_motors[index]["target"].as<string>()];
            devstat_t devstatus = (devstat_t)_codedic[_motors[index]["status"].as<string>()];

            return new CvtMotor (id, devtype, section, target, devstatus);
        } catch (...) {
            return nullptr;
        }
    }
};

} // namespace stdcvt
#endif
