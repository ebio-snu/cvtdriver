/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtdevice.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtDevice.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_DEVICE_
#define _CVT_DEVICE_

#include <iostream>
#include <string> 
#include <glog/logging.h>

#include "cvtcode.h"
#include "cvtconfig.h"
#include "cvtdevicespec.h"
#include "cvtcommand.h"

namespace stdcvt {

using namespace std;

/*
 @brief CvtDevice 는 개별 장비를 추상화한 클래스이다.
*/
class CvtDevice {
private:
    int _id;                //< 장비 ID
    CvtDeviceSpec _devspec; //< 장비의 스펙
    devstat_t _status;      //< 장비 상태

public:
    /**
     새로운 장비를 생성한다.
     @param devid 장비의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 장비의 상태
    */
    CvtDevice(int devid, devtype_t devtype, 
        devsec_t section, devtarget_t target, devstat_t devstatus) 
        : _devspec(devtype, section, target) {

        _id = devid;
        _status = devstatus;
    }

    ~CvtDevice() {
    }

    /**
     장비에 부여된 아이디를 리턴한다.
     @return 장비의 아이디
    */
    int getid() {
        return _id;
    }

    /**
     장비의 스펙을 리턴한다.
     @return 장비 스펙의 포인터
    */
    CvtDeviceSpec *getspec() {
        return &_devspec;
    }

    /**
     장비의 상태를 리턴한다.
     @return 장비의 상태
    */
    devstat_t getstatus () {
        return _status;
    }

    /**
     장비의 상태를 세팅한다.
     @param devstatus 새로 세팅할 장비의 상태
     @return 세팅된 장비의 상태
    */
    devstat_t setstatus (devstat_t devstatus) {
        _status = devstatus;
        return _status;
    }

    /**
     장비의 상태를 문자열로 내보낸다. 
    */
    string tostring() {
        return "CvtDevice(" + std::to_string(_id) + ") [" +  _devspec.tostring() 
            + "], status : " + std::to_string(_status);
    }
};

/*
 @brief CvtSensor는 CvtDevice를 상속하여, 개별 센서를 추상화한 클래스이다.
*/
class CvtSensor : public CvtDevice {
private:
    obsunit_t _unit;          //< 관측치의 단위
    double _value;            //< 센서의 관측치

public:

    /**
     새로운 센서를 생성한다.
     @param devid 센서의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 센서의 상태
     @param unit 관측치의 단위
    */
    CvtSensor (int devid, devtype_t devtype, devsec_t section, 
        devtarget_t target, devstat_t devstatus, obsunit_t unit) 
        : CvtDevice (devid, devtype, section, target, devstatus) {
        _unit = unit;
        _value = 0;
    }

    /**
     관측치 단위를 읽는다.
     @return 관측치 단위
    */
    obsunit_t getunit () {
        return _unit;
    }

    /**
     관측치 단위를 세팅한다.
     @param unit 새로 세팅할 관측치 단위
     @return 관측치 단위
    */
    obsunit_t setunit (obsunit_t unit) {
        _unit = unit;
        return _unit;
    }

    /**
     관측치를 기록한다.
     @param value 관측치
     @return 기록한 관측치값
    */
    double writeobservation (double value) {
        _value = value;
        return _value;
    }

    /**
     관측치를 읽는다.
     @return 관측치값
    */
    double readobservation () {
        return _value;
    }

    /**
     센서의 상태를 문자열로 내보낸다. 
    */
    string tostring() {
        return "CvtSensor [" + CvtDevice::tostring() 
            + "] observation : " + std::to_string(_value) 
            + ", unit : " + std::to_string(_unit);
    }
};

/*
 @brief CvtMotor는 CvtDevice를 상속하여, 개별 모터형 구동기를 추상화한 클래스이다.
*/
class CvtMotor : public CvtDevice {
private:
    double _ratio;      //< 현재 위치 비율. 0~1 사이의 값

public:
    /**
     새로운 모터형 구동기를 생성한다.
     @param devid 장비의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 장비의 상태
    */
    CvtMotor (int devid, devtype_t devtype, 
        devsec_t section, devtarget_t target, devstat_t devstatus) 
        : CvtDevice (devid, devtype, section, target, devstatus) {
    }

    /**
     모터형 구동기의 위치를 세팅한다.
     @param ratio 세팅할 위치
     @return 세팅된 위치
    */
    double setratio(double ratio) {
         _ratio = ratio;
         return _ratio;
    }

    /**
     모터형 구동기의 위치를 확인한다.
     @return 구동기의 위치
    */
    double getratio() {
        return _ratio;
    }

    /**
     모터형 구동기의 상태를 문자열로 내보낸다. 
    */
    string tostring() {
        return "CvtMotor [" + CvtDevice::tostring() 
            + "], ratio : " + std::to_string(_ratio);
    }
};

} // namespace stdcvt
#endif
