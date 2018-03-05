/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtspec.h
 @date 2018-03-05, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtSpec.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_SPEC_
#define _CVT_SPEC_

#include <iostream>
#include <string>

#include <glog/logging.h>

#include "cvtcode.h"
#include "cvtoption.h"

using namespace std;

namespace stdcvt {

/*
 @brief CvtSpec 은 컨버터의 스펙을 다룬다.
*/
class CvtSpec {
private:
    string _cvtserial;      ///< 컨버터 시리얼 번호
    int _manufacturercode;  ///< 컨버터를 할당 받은 제조사 코드

    int _cvtid;             ///< 컨버터 ID
    string _model;          ///< 컨버터 모델
    string _version;        ///< 컨버터 버전

public:
    /**
     새로운 컨버터스펙을 생성한다.
    */
    CvtSpec() {
        _cvtserial = "";
        _manufacturercode = 2000;
        _cvtid = 1;
        _model = "STDCVT_2018.03";
        _version = "1.00";
    }

    ~CvtSpec() {
    }
};

}
#endif
