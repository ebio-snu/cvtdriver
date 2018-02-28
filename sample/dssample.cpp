/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file dssample.h
 @date 2018-02-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for sample driver.
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#include <iostream>
#include <sstream>
#include <string>

#include <boost/config.hpp>

#include <glog/logging.h>

#include "../spec/cvtdevice.h"
#include "../spec/cvtdriver.h"

#define BUFSIZE     128

namespace ebiodriver {

using namespace std;
using namespace stdcvt;

class DSSensor : public CvtSensor {
public:
    DSSensor(int devid, stdcvt::devtype_t devtype, stdcvt::devsec_t section,
        stdcvt::devtarget_t target, stdcvt::devstat_t devstatus, stdcvt::obsunit_t unit)
        : stdcvt::CvtSensor (devid, devtype, section, target, devstatus, unit) {
    }
};

class DSMotor : public CvtMotor{
public:
    DSMotor(int devid, stdcvt::devtype_t devtype, stdcvt::devsec_t section,
        stdcvt::devtarget_t target, stdcvt::devstat_t devstatus)
        : stdcvt::CvtMotor(devid, devtype, section, target, devstatus) {
    }
};
class DSDevice : public CvtDevice{
public:
    DSDevice(int devid, stdcvt::devtype_t devtype, stdcvt::devsec_t section,
        stdcvt::devtarget_t target, stdcvt::devstat_t devstatus)
        : stdcvt::CvtDevice(devid, devtype, section, target, devstatus) {
    }
};

class DSDriver : public CvtDriver {
private:
    DSSensor _sensor;
    DSDevice _switch;
    DSMotor _motor;

public:
    /**
     새로운 DS드라이버를 생성한다.
     @param modelcode 모델코드
     @param apispec API 버전
    */
    DSDriver() : stdcvt::CvtDriver (2001, 100),
        _sensor(10, DT_SEN_TEMPERATURE, 10103000002, DO_ENV_ATMOSPHERE, DS_SEN_NORMAL, OU_CELSIUS),
        _motor(20, DT_MOT_SIDEWINDOW, 10103000002, DO_EQUIPMENT, DS_MOT_STOP),
        _switch(30, DT_SWC_FAN, 10103000002, DO_EQUIPMENT, DS_SWC_OFF) {
    }

    ~DSDriver () {
        finalize ();
    }

    /**
     드라이버 제작자가 부여하는 버전번호를 확인한다.
     @return 문자열 형식의 버전번호
    */
    const char *getversion () {
        return "V0.1.0";
    }

    /**
     드라이버 제작자가 부여하는 모델번호를 확인한다.
     @return 문자열 형식의 모델번호
    */
    const char *getmodel () {
        return "ebiods_v1";
    }

    /**
     드라이버 제조사명을 확인한다.
     컨버터에서는 제조사명을 로깅용도로만 사용한다.
     @return 문자열 형식의 제조사명
    */
    const char *getcompany () {
        return "EBIO lab. SNU.";
    }

    /**
     드라이버를 초기화 한다. 드라이버 동작을 위한 option 은 key-value 형식으로 전달된다.
     @param option 드라이버동작을 위한 옵션
     @return 초기화 성공 여부
    */
    bool initialize (CvtConfig option) {
        return true;
    }

    /**
     드라이버를 종료한다.
     @return 종료 성공 여부
    */
    bool finalize () {
        return true;
    }

    /**
     드라이버간 상태교환을 하기전에 호출되는 메소드로 전처리를 수행한다.
     @return 전처리 성공 여부
    */
    bool preprocess () {
        return true;
    }

    /**
     드라이버간 상태교환이 이루어진 이후에 호출되는 메소드로 후처리를 수행한다.
     @return 후처리 성공 여부
    */
    bool postprocess () {
        LOG(INFO) << _sensor.tostring ();
        LOG(INFO) << _motor.tostring ();
        LOG(INFO) << _switch.tostring ();
        return true;
    }

    /**
     드라이버가 관리하고 있는 장비의 포인터를 꺼내준다.
     @param index 얻고자 하는 장비의 인덱스 번호. 0에서 시작한다.
     @return 인덱스에 해당하는 장비의 포인터. NULL 이라면 이후에 장비가 없다는 의미이다.
    */
    CvtDevice *getdevice(int index) {
        switch (index) {
            case 0:
                return &_sensor;
            case 1:
                return &_motor;
            case 2:
                return &_switch;
            default:
                return NULL;
        }
    }

    /**
      전달된 장비의 정보를 획득한다. 
      다른 드라이버의 장비정보를 입력해주기 위해 컨버터가 호출한다.
      @param pdevice 다른 드라이버의 장비 포인터
      @return 성공여부. 관심이 없는 장비인 경우라도 문제가 없으면 true를 리턴한다.
     */
    bool sharedevice(CvtDevice *pdevice) {
        return true;
    }

    /**
      다른 드라이버가 관리하고 있는 장비를 제어하고자 할때 명령을 전달한다.
      명령을 전달하지 않는 드라이버라면 그냥 NULL을 리턴하도록 만들면 된다.
      @param index 얻고자 하는 명령의 인덱스 번호. 0에서 시작한다.
      @return 인덱스에 해당하는 명령의 포인터. NULL 이라면 이후에 명령이 없다는 의미이다.
     */
    CvtCommand *getcommand(int index) {
        return (CvtCommand *)0;
    }

    /**
      다른 드라이버로부터 명령을 받아 처리한다.
      @param pcmd 명령에 대한 포인터
      @return 실제 명령의 처리 여부가 아니라 명령을 수신했는지 여부이다. 해당 명령을 실행할 장비가 없다면 false이다.
     */
    bool control(CvtCommand *pcmd) {
        return false;
    }
};

extern "C" BOOST_SYMBOL_EXPORT DSDriver plugin;
DSDriver plugin;

} // namespace ebiodriver
