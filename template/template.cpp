/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file template.cpp
 @date 2018-03-20, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is a template for driver.
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#include <iostream>

#include <glog/logging.h>


#include "../spec/cvtdriver.h"

namespace templatedriver {

using namespace std;
using namespace stdcvt;

class SampleDriver : stdcvt::CvtDriver {
private:
    // 장비 관리를 위한 변수
    map<string, CvtSensor *> _sensor;
    map<string, CvtActuator *> _switch;
    map<string, CvtMotor *> _motor;
    vector<CvtDevice *> _devices;

public:
    /**
     새로운 드라이버를 생성한다.
    */
    SampleDriver()
        : stdcvt::CvtDriver (2001, 100) { // 2001 을 회사 코드에 맞게 변경한다.
    }

    ~SampleDriver () {
        finalize ();
    }

    /**
     드라이버 제작자가 부여하는 버전번호를 확인한다.
     @return 문자열 형식의 버전번호
    */
    string getversion () {
        return "V0.1.0";    // 버전을 적당히 바꾼다.
    }

    /**
     드라이버 제작자가 부여하는 모델번호를 확인한다.
     @return 문자열 형식의 모델번호
    */
    string getmodel () {
        return "ebionode_v1";   // 모델명을 적당히 바꾼다.
    }

    /**
     드라이버 제조사명을 확인한다.
     컨버터에서는 제조사명을 로깅용도로만 사용한다.
     @return 문자열 형식의 제조사명
    */
    string getcompany () {
        return "EBIO lab. SNU."; // 회사명을 적당히 바꾼다.
    }

    /**
     드라이버를 초기화 한다. 드라이버 동작을 위한 option 은 key-value 형식으로 전달된다.
     @param option 드라이버동작을 위한 옵션
     @return 초기화 성공 여부
    */
    bool initialize (CvtOption option) {
        // 드라이버 초기화를 위한 코드를 넣는다.
        return true;
    }

    /**
     드라이버를 종료한다.
     @return 종료 성공 여부
    */
    bool finalize () {
        // 드라이버 종료를 위한 코드를 넣는다.


        // 장비 정보 메모리 해제
        for (map<string, CvtSensor *>::iterator iter = _sensor.begin(); 
                                            iter != _sensor.end(); ++iter) {
            delete (*iter).second;
        }
        for (map<string, CvtMotor *>::iterator iter = _motor.begin(); 
                                            iter != _motor.end(); ++iter) {
            delete (*iter).second;
        }
        for (map<string, CvtActuator *>::iterator iter = _switch.begin(); 
                                            iter != _switch.end(); ++iter) {
            delete (*iter).second;
        }

        return true;
    }

    /**
     드라이버간 상태교환을 하기전에 호출되는 메소드로 전처리를 수행한다.
     @return 전처리 성공 여부
    */
    bool preprocess () {
        // 전처리가 필요한 경우 전처리 코드를 넣는다.
        return true;
    }

    /**
     드라이버간 상태교환이 이루어진 이후에 호출되는 메소드로 후처리를 수행한다.
     @return 후처리 성공 여부
    */
    bool postprocess () {
        // 후처리가 필요한 경우 후처리 코드를 넣는다.
        return true;
    }

    /**
     드라이버가 관리하고 있는 장비의 포인터를 꺼내준다.
     @param index 얻고자 하는 장비의 인덱스 번호. 0에서 시작한다.
     @return 인덱스에 해당하는 장비의 포인터. NULL 이라면 이후에 장비가 없다는 의미이다.
    */
    CvtDevice *getdevice(int index) {
        try {
            return _devices.at(index);
        } catch (...) {
            return (CvtDevice *)0;
        }
    }

    /**
      전달된 장비의 정보를 획득한다. 
      다른 드라이버의 장비정보를 입력해주기 위해 컨버터가 호출한다.
      일반적인 업체별 드라이버에서는 특별히 구현하지 않아도 된다.
      @param pdevice 다른 드라이버의 장비 포인터
      @return 성공여부. 관심이 없는 장비인 경우라도 문제가 없으면 true를 리턴한다.
    */
    bool sharedevice(CvtDevice *pdevice) {
        return true;
    }

    /**
      다른 드라이버가 관리하고 있는 장비를 제어하고자 할때 명령을 전달한다.
      명령을 전달하지 않는 드라이버라면 그냥 NULL을 리턴하도록 만들면 된다.
      DSDriver 에서는 구현할 필요가 없기 때문에,
      일반적인 업체별 드라이버에서는 구현하지 않아도 된다.
      @param index 얻고자 하는 명령의 인덱스 번호. 0에서 시작한다.
      @return 인덱스에 해당하는 명령의 포인터. NULL 이라면 이후에 명령이 없다는 의미이다.
    */
    CvtCommand *getcommand(int index) {
        return (CvtCommand *)0;
    }

    /**
      다른 드라이버로부터 명령을 받아 처리한다.
      구동기를 다루어야 한다면 구현이 되어야 한다.
      @param pcmd 명령에 대한 포인터
      @return 실제 명령의 처리 여부가 아니라 명령을 수신했는지 여부이다. 해당 명령을 실행할 장비가 없다면 false이다.
    */
    bool control(CvtCommand *pcmd) {
        CvtRatioCommand *prcmd;
        bool ret = false;

        if ((prcmd = dynamic_cast<CvtRatioCommand *>(pcmd)) != nullptr) {
            for (map<string, CvtMotor *>::iterator iter = _motor.begin(); 
                                                iter != _motor.end(); ++iter) {
                CvtMotor *pmot = (*iter).second;
                if ((pmot->getspec())->ismatched (pcmd->getdevspec())) {
                    pmot->order (prcmd);
                    ret = true;
                }
            }

        } else {
            for (map<string, CvtActuator *>::iterator iter = _switch.begin(); 
                                                iter != _switch.end(); ++iter) {
                CvtActuator *pswc = (*iter).second;
                if ((pswc->getspec())->ismatched (pcmd->getdevspec())) {
                    pswc->order (pcmd);
                    ret = true;
                }
            }
        }

        return ret;
    }
};

extern "C" BOOST_SYMBOL_EXPORT DSSampleDriver plugin;
DSSampleDriver plugin;

} // namespace ebiodriver

