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
#include "cvtoption.h"

using namespace std;

namespace stdcvt {

/*
 @brief CvtDeviceSpec is a virtual class for a smartfarm device.
*/
class CvtDeviceSpec {
private:
    string _manufacturer;   //< 장비 제조사
    string _model;          //< 장비 모델
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
        _manufacturer = "";
        _model = "";
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
     장비의 제조사를 세팅한다.
     @param manufacturer 장비 제조사
     @return 세팅된 장비 제조사
    */
    string setmanufacturer(string manufacturer) {
        _manufacturer = manufacturer;
        return _manufacturer;
    }

    /**
     장비의 제조사를 확인한다.
     @return 세팅된 장비 제조사
    */
    string getmanufacturer() {
        return _manufacturer;
    }

    /**
     장비의 모델을 세팅한다.
     @param model 장비 모델
     @return 세팅된 장비 모델
    */
    string setmodel(string model) {
        _model = model;
        return _model;
    }

    /**
     장비의 모델을 확인한다.
     @return 세팅된 장비 모델
    */
    string getmodel() {
        return _model;
    }

    /**
     장비의 속성을 복사한다.
     @param pdevspec 복사할 소스 장비스펙에 대한 포인터
    */
    bool copyspec(CvtDeviceSpec *pdevspec) {
        _type = pdevspec->_type;
        _section = pdevspec->_section;
        _target = pdevspec->_target;
        _manufacturer = pdevspec->_manufacturer;
        _model = pdevspec->_model;
        return true;
    }

    /**
      장비의 스펙을 문자열로 내보낸다. 
    */
    string tostring() {
        return "CvtDeviceSpec type : " + to_string(_type) 
            + ", target : " + to_string(_target) + ", section : " + to_string(_section)
            + ", manufacturer : " + _manufacturer + ", model : " + _model;
    }
};

}
#endif
