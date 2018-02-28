/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtcommand.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is a template of CvtCommand.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_COMMAND_
#define _CVT_COMMAND_

#include "cvtdevicespec.h"

namespace stdcvt {

/*
 @brief CvtCommand 는 개별 장비에 전달할 명령 클래스이다. 기본적으로 켜고, 끄는 기능만 가지고 있다.
*/
class CvtCommand {
private:
    int _id;                    //< 명령 ID
    CvtDeviceSpec *_pdevspec;   //< 명령 수행 장비의 스펙
    bool _onoff;                //< on/off 명령 true면 on

public:
    /**
     새로운 명령를 생성한다.
     @param cmdid 명령의 아이디
     @param pdev  명령을 수행할 장비의 포인터
    */
    CvtCommand(int cmdid, CvtDeviceSpec *pdevspec) {
        _id = cmdid;
        _pdevspec = pdevspec;
    }

    ~CvtCommand();

    /**
     명령에 부여된 아이디를 리턴한다.
     @return 명령의 아이디
    */
    int getid() {
        return _id;
    }

    /**
     on/off 명령을 확인한다.
     @return on이면 true
    */
    bool getonoff() {
        return _onoff;
    }

    /**
     on/off 명령을 세팅한다.
     @param onoff on이면 true
     @return 세팅된 상태.
    */
    bool setonoff (bool onoff) {
        _onoff = onoff;
        return _onoff;
    }
};

/*
 @brief CvtRatioCommand 는 목표비율을 지정하기위한 명령으로, CvtCommand를 상속한다. 개폐기와 같은 모터형 구동기에 어울리는 명령이다.
*/
class CvtRatioCommand : public CvtCommand {
private:
    double _ratio;          //< 타겟 비율. 0~1 사이값으로 한다.
public:
    /**
     지정된 비율값을 확인한다.
     @return ratio 값
    */
    double getratio () {
        return _ratio;
    }

    /**
     지정된 비율값을 세팅한다.
     @param ratio
     @return 세팅된 비율값
    */
    double setratio (double ratio) {
        _ratio = ratio;
        return _ratio;
    }
};

} // namespace stdcvt
#endif
