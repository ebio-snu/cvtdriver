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

typedef enum {
    _DS_TX = 0,
    _DS_TY = 1,
    _DS_TZ = 2,
    _DS_PX = 3,
    _DS_PY = 4,
    _DS_PZ = 5,
} _dsiv_t;

#define _DS_MAX 6

/*
 @brief CvtDeviceSpec is a virtual class for a smartfarm device.
*/
class CvtDeviceSpec {
private:
    string _manufacturer;   ///< 장비 제조사
    string _model;          ///< 장비 모델
    devtype_t _type;        ///< 장비 종류
    devsec_t _section;      ///< 장비 설치 구역
    devtarget_t _target;    ///< 장비의 대상

    class CvtDeviceSection {
    private:
        int _sv[_DS_MAX];     ///<  전체 x

    public:
        CvtDeviceSection(long section) {
            long tmp = section;
            for (int i = 0; i < _DS_MAX; i++) {
                _sv[i] = tmp % 100;
                tmp = tmp / 100;
            }
        }

        int getvalue(_dsiv_t index) {
            return _sv[index];
        }
    };

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
     장비그룹의 종류를 리턴한다.
     @return 장비그룹의 종류
    */
    devgroup_t getgrouptype() {
        return (devgroup_t)(_type / 10000);
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

    /**
     장비 작동대상이 매치되는지 확인한다.
     @param pdevspec 확인할 소스 장비스펙에 대한 포인터
    */
    bool checktarget(CvtDeviceSpec *pdevspec) {
        if ((_target == DO_UNKNOWN) || 
            (pdevspec->_target == DO_UNKNOWN)) {
            return false;
        }
        if (_target == pdevspec->_target)
            return true;
        // 설치 위치가 있는 장비와 설치 위치가 없는 상태의 장비에 대해
        // 지능적 처리가 필요할 수 있지만 현재는 무시한다.
        return false;
    }

    /**
     장비타입이 매치되는지 확인한다.
     @param pdevspec 확인할 소스 장비스펙에 대한 포인터
    */
    bool checktype(CvtDeviceSpec *pdevspec) {
        if ((_type == DT_DEV_UNKNOWN) || (_type == DT_SEN_UNKNOWN) || 
            (_type == DT_MOT_UNKNOWN) || (_type == DT_SWC_UNKNOWN) || 
            (pdevspec->_type == DT_SEN_UNKNOWN) || 
            (pdevspec->_type == DT_MOT_UNKNOWN) || 
            (pdevspec->_type == DT_SWC_UNKNOWN) || 
            (pdevspec->_type == DT_DEV_UNKNOWN)) {
            return false;
        }
        if (_type == pdevspec->_type)
            return true;

        // 창이 다겹인경우 장비 타입에 대해서
        // 지능적 처리가 필요할 수 있지만 현재는 무시한다.
        return false;
    }

    /**
     장비설치위치가 매치되는지 확인한다.
     @param pdevspec 확인할 소스 장비스펙에 대한 포인터
    */
    bool checksection(CvtDeviceSpec *pdevspec) {
        if ((_section == DL_UNKNOWN) || 
            (pdevspec->_section == DL_UNKNOWN)) {
            return false;
        }
        if (_section == pdevspec->_section) {
            return true;
        }

        CvtDeviceSection in(_section);
        CvtDeviceSection ex(pdevspec->_section);

        if (in.getvalue (_DS_TX) == ex.getvalue (_DS_TX)) {
            if (in.getvalue (_DS_PX) != ex.getvalue (_DS_PX)) {
                return false;   // x축 방향으로 같은 개수인데 다른 위치
            }
        } else {
            // x축 방향으로 다른 개수. 서로 다른 구역구분을 가지고 있는 경우.
            // 지능적으로 처리할 수 있지만 여기서는 단순히 처리함.
            return false;
        }

        if (in.getvalue (_DS_TY) == ex.getvalue (_DS_TY)) {
            if (in.getvalue (_DS_PY) != ex.getvalue (_DS_PY)) {
                return false;   // Y축 방향으로 같은 개수인데 다른 위치
            }
        } else {
            // Y축 방향으로 다른 개수. 서로 다른 구역구분을 가지고 있는 경우.
            // 지능적으로 처리할 수 있지만 여기서는 단순히 처리함.
            return false;
        }

        if (in.getvalue (_DS_TZ) == ex.getvalue (_DS_TZ)) {
            if (in.getvalue (_DS_PZ) != ex.getvalue (_DS_PZ)) {
                return false;   // Z축 방향으로 같은 개수인데 다른 위치
            }
        } else {
            // Z축 방향으로 다른 개수. 서로 다른 구역구분을 가지고 있는 경우.
            // 지능적으로 처리할 수 있지만 여기서는 단순히 처리함.
            return false;
        }

        return true;
    }
        
    /**
     장비스펙이 매치되는지 확인한다.
     @param pdevspec 확인할 소스 장비스펙에 대한 포인터
    */
    bool ismatched(CvtDeviceSpec *pdevspec) {
        if (!checksection (pdevspec))
            return false;

        if (!checktarget (pdevspec))
            return false;

        if (!checktype (pdevspec))
            return false;

        return true;
    }
};

}
#endif
