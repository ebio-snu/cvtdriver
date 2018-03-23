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
#include "cvtdevicespec.h"
#include "cvtcommand.h"

using namespace std;

namespace stdcvt {

/*
 @brief CvtDevice 는 개별 장비를 추상화한 클래스이다.
*/
class CvtDevice {
private:
    string _id;             ///< 장비 ID
    CvtDeviceSpec _devspec; ///< 장비의 스펙
    devstat_t _status;      ///< 장비 상태

protected:
    void _copy(CvtDevice *pdevice) {
        _id = pdevice->_id;
        _devspec.copy (pdevice->getspec ());
        _status = pdevice->_status;
    }

public:

    /**
     새로운 장비를 생성한다.
     @param devid 장비의 아이디
     @param pdevspec 장비의 스펙
     @param devstatus 장비의 상태
    */
    CvtDevice(string devid, CvtDeviceSpec *pdevspec, devstat_t devstatus) {
        _id = devid;
        _devspec.copy (pdevspec);
        _status = devstatus;
    }

    /**
     새로운 장비를 생성한다.
     @param devid 장비의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 장비의 상태
    */
    CvtDevice(string devid, devtype_t devtype, 
        devsec_t section, devtarget_t target, devstat_t devstatus) 
        : _devspec(devtype, section, target) {

        _id = devid;
        _status = devstatus;
    }

    virtual ~CvtDevice() {
    }

    /**
     장비에 부여된 아이디를 리턴한다.
     @return 장비의 아이디
    */
    string getid() {
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
        return "CvtDevice(" + _id + ") [" +  _devspec.tostring() 
            + "], status : " + std::to_string(_status);
    }
    
    /**
     장비의 클론을 만든다.
     @return 클론의 포인터
    */
    virtual CvtDevice *clone() = 0;

    /**
     장비 정보를 복사한다.
     @return 복사가 성공하면 true.
    */
    virtual bool copy(CvtDevice *pdevice) = 0;

    /**
     장비 그룹정보를 확인한다.
    */
    static devgroup_t getgroup(devtype_t devtype) {
        return (devgroup_t) (devtype / 10000);
    }
};

/*
 @brief CvtSensor는 CvtDevice를 상속하여, 개별 센서를 추상화한 클래스이다.
*/
class CvtSensor : public CvtDevice {
private:
    obsunit_t _unit;          ///< 관측치의 단위
    double _value;            ///< 센서의 관측치

public:
    /**
     새로운 센서를 생성한다.
     @param devid 센서의 아이디
     @param pdevspec 장비 스펙
     @param devstatus 센서의 상태
     @param unit 관측치의 단위
    */
    CvtSensor (string devid, CvtDeviceSpec *pdevspec, 
                    devstat_t devstatus, obsunit_t unit) 
        : CvtDevice (devid, pdevspec, devstatus) {
        _unit = unit;
        _value = 0;
    }

    /**
     새로운 센서를 생성한다.
     @param devid 센서의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 센서의 상태
     @param unit 관측치의 단위
    */
    CvtSensor (string devid, devtype_t devtype, devsec_t section, 
        devtarget_t target, devstat_t devstatus, obsunit_t unit) 
        : CvtDevice (devid, devtype, section, target, devstatus) {
        _unit = unit;
        _value = 0;
    }

    /**
     장비의 클론을 만든다.
     @return 클론의 포인터
    */
    CvtDevice *clone() {
        CvtSensor *psensor = new CvtSensor(getid(), getspec(), getstatus(), _unit);
        if (psensor) {
            psensor->writeobservation (_value);
            return (CvtDevice *)psensor;
        }
        return nullptr;
    }

    /**
     장비 정보를 복사한다.
     @return 복사가 성공하면 true.
    */
    bool copy(CvtDevice *pdevice) {
        CvtSensor *psensor = dynamic_cast<CvtSensor *>(pdevice);
        if (psensor) {
            _copy (pdevice);
            _unit = psensor->_unit;
            _value = psensor->_value;
            return true;
        }
        return false;
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
        return "CvtSensor [" + CvtDevice::tostring () 
            + "] observation : " + std::to_string (_value) 
            + ", unit : " + std::to_string (_unit);
    }
};

/*
 @brief CvtActuator는 CvtDevice를 상속하여, 개별 구동기를 추상화한 클래스이다.
*/
class CvtActuator : public CvtDevice {
private:
    int _lastcmdid;     ///< 마지막 명령 ID. 명령이 처리된 이후에 0으로 바꾼다.
    bool _onoff;        ///< on/off 명령

protected:
    /**
     명령을 세팅한다. order 구현시 한번씩 호출해주면 최종 아이디를 기억하도록 한다.
     @param pcmd 명령에 대한 포인터
    */
    void setcommand (CvtCommand *pcmd) {
        _lastcmdid = pcmd->getid ();
    }

public:
    /**
     새로운 구동기를 생성한다.
     @param devid 장비의 아이디
     @param pdevspec 장비의 스펙
     @param devstatus 장비의 상태
    */
    CvtActuator(string devid, CvtDeviceSpec *pdevspec, devstat_t devstatus) 
        : CvtDevice (devid, pdevspec, devstatus) {
        _lastcmdid = -1;
        _onoff = false; // off
    }

    /**
     새로운 구동기를 생성한다.
     @param devid 장비의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 장비의 상태
    */
    CvtActuator(string devid, devtype_t devtype, 
        devsec_t section, devtarget_t target, devstat_t devstatus) 
        : CvtDevice (devid, devtype, section, target, devstatus) {
        _lastcmdid = -1;
        _onoff = false; // off
    }

    /**
     장비의 클론을 만든다.
     @return 클론의 포인터
    */
    CvtDevice *clone() {
        CvtActuator *pactuator = new CvtActuator(getid(), getspec(), getstatus());
        if (pactuator) {
            pactuator->copy (this);
            return (CvtDevice *)pactuator;
        }
        return nullptr;
    }

    /**
     장비 정보를 복사한다.
     @return 복사가 성공하면 true.
    */
    bool copy(CvtDevice *pdevice) {
        CvtActuator *pactuator = dynamic_cast<CvtActuator *>(pdevice);
        if (pactuator) {
            _copy (pdevice);
            _lastcmdid = pactuator->_lastcmdid;
            _onoff = pactuator->_onoff;
            return true;
        }
        return false;
    }

    /**
     최종 명령의 아이디를 확인한다.
     @return 최종 명령의 아이디. 없을경우 -1
    */
    int getlastcmdid () {
        return _lastcmdid;
    }

    /**
     장비를 작동시킨다.
     @return 작동상태. true 면 on.
    */
    bool turnon () {
        _onoff = true;
        return _onoff;
    }

    /**
     장비를 작동을 중지한다.
     @return 작동상태. true 면 on.
    */
    bool turnoff () {
        _onoff = false;
        return _onoff;
    }

    /**
     장비작동명령을 확인한다.
     @return 작동상태. true 면 on.
    */
    bool getonoff () {
        return _onoff;
    }

    /**
     명령을 지시한다. 
     실제 실행하는 것은 아니고 내부에 명령을 저장하고 있다가 실제 장비에게 전달하는 역할을 담당한다.
     @param pcmd 명령의 포인터
     @return 명령 저장 여부. 
    */
    bool order(CvtCommand *pcmd) {
        pcmd->getonoff() ? turnon() : turnoff();
        setcommand (pcmd);
        return true;
    }

    /**
     전달완료된 명령아이디를 세팅한다.
     @param cmdid 전달완료된 명령아이디
    */
    void executed(int cmdid) {
        if (cmdid >= _lastcmdid)
            _lastcmdid = 0;
    }

    /**
     구동기의 상태를 문자열로 내보낸다. 
     @return 구동기의 상태 문자열
    */
    string tostring() {
        return "CvtActuator [" + CvtDevice::tostring() 
            + "], lastcmdid : " + std::to_string(getlastcmdid())
            + ", onoff : " + std::to_string(getonoff());
    }
};

/*
 @brief CvtMotor는 CvtActuator를 상속하여, 개별 모터형 구동기를 추상화한 클래스이다.
*/
class CvtMotor : public CvtActuator {
private:
    double _current;      ///< 현재 위치 비율. 0~1 사이의 값
    double _target;       ///< 목표 위치 비율. 0~1 사이의 값

public:
    /**
     새로운 모터형 구동기를 생성한다.
     @param devid 장비의 아이디
     @param pdevspec 장비의 스펙
     @param devstatus 장비의 상태
    */
    CvtMotor (string devid, CvtDeviceSpec *pdevspec, devstat_t devstatus) 
        : CvtActuator (devid, pdevspec, devstatus) {
        _current = 0;
        _target = 0;
    }

    /**
     새로운 모터형 구동기를 생성한다.
     @param devid 장비의 아이디
     @param devtype 장비의 종류
     @param section 장비 설치 구역
     @param target 장비의 대상
     @param devstatus 장비의 상태
    */
    CvtMotor (string devid, devtype_t devtype, 
        devsec_t section, devtarget_t target, devstat_t devstatus) 
        : CvtActuator (devid, devtype, section, target, devstatus) {
        _current = 0;
        _target = 0;
    }

    /**
     장비의 클론을 만든다.
     @return 클론의 포인터
    */
    CvtDevice *clone() {
        CvtMotor *pmotor = new CvtMotor(getid(), getspec(), getstatus());
        if (pmotor) {
            pmotor->copy (this);
            return (CvtDevice *)pmotor;
        }
        return nullptr;
    }

    /**
     장비 정보를 복사한다.
     @return 복사가 성공하면 true.
    */
    bool copy(CvtDevice *pdevice) {
        CvtMotor *pmotor = dynamic_cast<CvtMotor *>(pdevice);
        if (pmotor) {
            pmotor->CvtActuator::copy(pdevice);
            _current = pmotor->_current;
            _target = pmotor->_target;
            return true;
        }
        return false;
    }

    /**
     모터형 구동기의 목표 위치를 세팅한다.
     @param ratio 세팅할 위치
     @return 세팅된 위치
    */
    double settarget(double ratio) {
        _target= ratio;
        return _target;
    }

    /**
     모터형 구동기의  목표 위치를 확인한다.
     @return 구동기의 위치
    */
    double gettarget() {
        return _target;
    }

    /**
     모터형 구동기의 현재 위치를 세팅한다.
     @param ratio 현재  위치
     @return 현재 위치
    */
    double setcurrent(double ratio) {
        _current = ratio;
        return _current;
    }

    /**
     모터형 구동기의 현재 위치를 확인한다.
     @return 구동기의 위치
    */
    double getcurrent() {
        return _current;
    }

    /**
     모터형 구동기의 상태를 문자열로 내보낸다. 
     @return 모터형 구동기의 상태 문자열
    */
    string tostring() {
        return "CvtMotor [" + CvtDevice::tostring() 
            + "], lastcmdid : " + std::to_string(getlastcmdid())
            + "], current : " + std::to_string(_current)
            + ", onoff : " + std::to_string(getonoff())
            + ", target : " + std::to_string(_target);
    }

    /**
     명령을 지시한다. 
     실제 실행하는 것은 아니고 내부에 명령을 저장하고 있다가 실제 장비에게 전달하는 역할을 담당한다.
     @param pcmd 명령의 포인터
     @return 실행명령이 저장되면 true, 실행할 명령이 아니면 false
    */
    bool order(CvtCommand *pcmd) {
        CvtRatioCommand *prcmd = dynamic_cast<CvtRatioCommand *>(pcmd);
        if (prcmd == nullptr) {
            return false;
        }

        if (prcmd->getonoff()) {
            // on
            settarget (prcmd->getratio ());
            turnon ();
        } else {
            // off
            turnoff ();
        }
        setcommand (pcmd);
        return true;
    }
};

} // namespace stdcvt
#endif
