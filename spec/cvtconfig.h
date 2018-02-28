/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtconfig.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtConfig.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_CONFIG_
#define _CVT_CONFIG_

namespace stdcvt {

/*
 @brief CvtConfig is a virtual class for a smartfarm device.
*/
class CvtConfig {
private:
    void *_object;

public:
    /**
     새로운 옵션를 생성한다.
    */
    CvtConfig() {
        _object = (void *) 0;
    }

    ~CvtConfig() {
    }

    /**
     옵션의 값을 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 값
    */
    char *get (char *key) {
        return "/dev/ttyACM0";
    }

    /**
     옵션의 값을 정수형으로 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 값
    */
    int getint (char *key) {
        return 9600;
    }

    /**
     옵션의 값을 void *로 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 값
    */
    void *getobject (char *key) {
        return (void *)_object;
    }

    /**
     옵션의 값을 세팅한다.
     @param key 옵션을 선택하기 위한 키
     @param object 옵션값
     @return 옵션의 값
    */
    void *setobject (char *key, void *object) {
        _object = object;
        return (void *)_object;
    }
};

} // namespace stdcvt
#endif
