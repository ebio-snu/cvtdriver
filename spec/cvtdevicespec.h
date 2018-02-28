/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtdevicespec.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtDeviceSpec.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_DEVICESPEC_
#define _CVT_DEVICESPEC_

#include <iostream>
#include <string>

#include <glog/logging.h>

#include "cvtcode.h"
#include "cvtconfig.h"

using namespace std;

namespace stdcvt {

/*
 @brief CvtDeviceSpec is a virtual class for a smartfarm device.
*/
class CvtDeviceSpec {
private:
    devtype_t _type;        //< 장비 종류
    devsec_t _section;      //< 장비 설치 구역
    devtarget_t _target;    //< 장비의 대상

public:
    /**
     새로운 장비스펙을 생성한다.
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
    */
    CvtDeviceSpec(devtype_t devtype, devsec_t section, devtarget_t target) {
        _type = devtype;
        _section = section;
        _target = target;
    }

    ~CvtDeviceSpec() {
    }

    /**
     장비의 종류를 리턴한다.
     @return 장비의 종류
    */
    devtype_t gettype() {
        return _type;
    }

    /**
     장비의 설치구역을 리턴한다.
     @return 장비의 설치구역
    */
    devsec_t getsection() {
        return _section;
    }

    /**
     장비의 대상을 리턴한다.
     @return 장비의 대상
    */
    devtarget_t gettarget() {
        return _target;
    }

    /**
     장비의 속성을 복사한다.
     @param pdev 복사할 소스 장비스펙에 대한 포인터
    */
    bool copyspec(CvtDeviceSpec *pdevspec) {
        _type = pdevspec->_type;
        _section = pdevspec->_section;
        _target = pdevspec->_target;
        return true;
    }

    /**
      장비의 스펙을 문자열로 내보낸다. 
    */
    string tostring() {
        return "CvtDeviceSpec type : " + std::to_string(_type) 
            + ", target : " + std::to_string(_target) + ", section : " + std::to_string(_section);
    }

};

}
#endif
