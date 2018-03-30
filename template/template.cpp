/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file template.cpp
 @date 2018-03-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is a template for cvtdriver
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#include <iostream>
#include <sstream>
#include <string>

#include <glog/logging.h>

// 적당한 네임스페이스를 만드세요.
namespace template_driver {

using namespace std;
using namespace stdcvt;

// 적당한 클래스이름을 만드세요~
class DSTemplateDriver : stdcvt::CvtDriver {
private:
    // 장비와 통신을 위한 변수를 추가하세요~

    // 장비 관리를 위한 변수입니다. 다른 방법으로 처리하셔도 됩니다.
    map<string, CvtSensor *> _sensor;
    map<string, CvtActuator *> _switch;
    map<string, CvtMotor *> _motor;
    vector<CvtDevice *> _devices;

    // 설정파일에서 관리하는 장비를 로딩하여 초기화를 수행합니다.
    // 별도의 방법을 사용하신다면 필요없는 함수 입니다.
    void loaddevices(CvtDeviceFactory *pdevfac) {
        CvtSensor *psensor;
        for (int i = 0; (psensor = pdevfac->newsensor(i)) != nullptr; i++) {
            LOG(INFO) << "add sensor: " << psensor->tostring ();
            _sensor[psensor->getid ()] = psensor;
            _devices.push_back(psensor);
        }
        CvtMotor *pmotor;
        for (int i = 0; (pmotor = pdevfac->newmotor(i)) != nullptr; i++) {
            LOG(INFO) << "add motor: " << pmotor->tostring ();
            _motor[pmotor->getid ()] = pmotor;
            _devices.push_back(pmotor);
        }
        CvtActuator *pswitch;
        for (int i = 0; (pswitch = pdevfac->newswitch(i)) != nullptr; i++) {
            LOG(INFO) << "add switch: " << pswitch->tostring ();
            _switch[pswitch->getid ()] = pswitch;
            _devices.push_back(pswitch);
        }
    }



public:
    /**
     새로운 DS드라이버를 생성한다.
    */
    DSSampleDriver()
        : stdcvt::CvtDriver (2001, 100) {
    }

    ~DSSampleDriver () {
    }

    /**
     드라이버 제작자가 부여하는 버전번호를 확인한다.
     적당한 값으로 넣으시면 됩니다.
     @return 문자열 형식의 버전번호
    */
    string getversion () {
        return "V0.1.0";
    }

    /**
     드라이버 제작자가 부여하는 모델번호를 확인한다.
     적당한 값으로 넣으시면 됩니다.
     @return 문자열 형식의 모델번호
    */
    string getmodel () {
        return "ebionode_v1";
    }

    /**
     드라이버 제조사명을 확인한다.
     컨버터에서는 제조사명을 로깅용도로만 사용한다.
     적당한 값으로 넣으시면 됩니다.
     @return 문자열 형식의 제조사명
    */
    string getcompany () {
        return "EBIO lab. SNU.";
    }

    /**
     드라이버를 초기화 한다. 드라이버 동작을 위한 option 은 key-value 형식으로 전달된다.
     @param option 드라이버동작을 위한 옵션
     @return 초기화 성공 여부
    */
    bool initialize (CvtOption option) {
        LOG (INFO) << "DSSampleDriver initialize.";
        // load device
        // 설정파일에서 장비정보를 로딩하는 방법을 사용한다면 지우지 마세요.
        loaddevices (option.getdevfactory());

        // 여기에 필요한 초기화 작업을 기술하시면 됩니다.

        return true;
    }

    /**
     드라이버를 종료한다.
     @return 종료 성공 여부
    */
    bool finalize () {
        LOG (INFO) << "DSSampleDriver finalize.";
        for (map<string, CvtSensor *>::iterator iter = _sensor.begin(); 
                                            iter != _sensor.end(); ++iter) {
            delete (*iter).second;
        }
        _sensor.clear ();
        for (map<string, CvtMotor *>::iterator iter = _motor.begin(); 
                                            iter != _motor.end(); ++iter) {
            delete (*iter).second;
        }
        _motor.clear ();
        for (map<string, CvtActuator *>::iterator iter = _switch.begin(); 
                                            iter != _switch.end(); ++iter) {
            delete (*iter).second;
        }
        _switch.clear ();

        // 여기에 필요한 작업종료를 위한 내용을 기술하시면 됩니다.

        return true;
    }

    /**
     드라이버간 상태교환을 하기전에 호출되는 메소드로 전처리를 수행한다.
     @return 전처리 성공 여부
    */
    bool preprocess () {
        // 전처리가 필요하다면 여기에 작성합니다.
        // 비동기적으로 메세지를 처리하지 않으신다면, 
        // 여기서 센서데이터 혹은 구동기 상태정보를 읽어오시면 됩니다.

        return true;
    }

    /**
     드라이버간 상태교환이 이루어진 이후에 호출되는 메소드로 후처리를 수행한다.
     @return 후처리 성공 여부
    */
    bool postprocess () {
        // 후처리가 필요하다면 여기에 작성합니다.
        // 여기서 구동기 명령을 자사의 장비로 전달하시면 됩니다.

        return true;
    }

    /**
     드라이버가 관리하고 있는 장비의 포인터를 꺼내준다.
     @param index 얻고자 하는 장비의 인덱스 번호. 0에서 시작한다.
     @return 인덱스에 해당하는 장비의 포인터. NULL 이라면 이후에 장비가 없다는 의미이다.
    */
    CvtDevice *getdevice(int index) {
        // 위에서 장비에 대한 맵을 그냥 사용하신다면 변경하실 필요가 없습니다.
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
        // 다른 드라이버에 제공하는 센서데이터나 구동기 상태를 처리하고자 한다면 작성하셔야 합니다.
        // 일반적으로는 작성하지 않으셔도 됩니다.
        return true;
    }

    /**
      다른 드라이버가 관리하고 있는 장비를 제어하고자 할때 명령을 전달한다.
      명령을 전달하지 않는 드라이버라면 그냥 NULL을 리턴하도록 만들면 된다.
      DSDriver 에서는 구현할 필요가 없다.
      @return 명령의 포인터. NULL 이라면 이후에 명령이 없다는 의미이다.
    */
    CvtCommand *getcommand() {
        // 작성하실 필요 없습니다.
        return (CvtCommand *)0;
    }

    /**
      다른 드라이버로부터 명령을 받아 처리한다.
      구동기를 다루어야 한다면 구현이 되어야 한다.
      @param pcmd 명령에 대한 포인터
      @return 실제 명령의 처리 여부가 아니라 명령을 수신했는지 여부이다. 해당 명령을 실행할 장비가 없다면 false이다.
    */
    bool control(CvtCommand *pcmd) {
        // 장비에 대한 맵을 그대로 사용한다면 수정하실 필요 없습니다.
        // 다른 방식을 원하시면 수정하시면 됩니다.
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

