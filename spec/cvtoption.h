/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtoption.h
 @date 2018-03-03, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtOption.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_OPTION_
#define _CVT_OPTION_

#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/json_query.hpp>

using namespace std;

using jsoncons::json;
using jsoncons::jsonpath::json_query;

namespace stdcvt {

/*
 @brief CvtOption는 설정파일에 포함된 드라이버관련 설정을 전달하기 위한 클래스이다.
 설정파일에 포함되지 않았지만 드라이버 운영에 필요할 수 있는 객체를 전달하기 위한 용도로도 활용될 수 있다.
*/
class CvtOption {
private:
    map<string, void *> _objects;   ///< 컨버터에서 등록해주는 Objects
    json *_poption;                 ///< 설정파일에서 드라이버에 할당된 옵션

public:
    /**
     새로운 옵션를 생성한다.
     @param poption 특정 드라이버를 위한 옵션. json 타입의 포인터.
    */
    CvtOption(json *poption) {
        _poption = poption;
    }

    ~CvtOption() {
    }

    /**
     복잡한 옵션을 사용하고자 할때에는 옵션의 값을 리턴한다.
     @param path JSONPATH 로 나타낸 경로
     @return 옵션의 값
    */
    json getjson (string path) {
        string _path = "$." + path;
        json ret = json_query(*_poption, path); 
        return ret;
    }

    /**
     옵션의 값을 문자열로 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 문자열 값
    */
    string get (string key) {
        json ret = (*_poption)[key];
        return ret.as<string>();
    }

    /**
     옵션의 값을 실수형으로 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 실수형값
    */
    double getdouble (string key) {
        json ret = (*_poption)[key];
        return ret.as<double>();
    }

    /**
     옵션의 값을 정수형으로 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 값
    */
    int getint (string key) {
        json ret = (*_poption)[key];
        return ret.as<int>();
    }

    /**
     옵션의 값을 void *로 리턴한다.
     @param key 옵션을 선택하기 위한 키
     @return 옵션의 값
    */
    void *getobject (string key) {
        map<string, void *>::iterator iter;
        iter = _objects.find (key);
        return (void *)(iter->second);
    }

    /**
     옵션의 값을 세팅한다.
     @param key 옵션을 선택하기 위한 키
     @param object 옵션값
     @return 옵션의 값
    */
    void *setobject (string key, void *object) {
        pair<map<string, void *>::iterator,bool> ret;

        ret = _objects.insert (pair<string , void *> (key, object));
        if (ret.second == false) {
            LOG(INFO) << "setobject fail : " << key << " already existed.";
        }

        return (void *)(ret.first->second);
    }
};

} // namespace stdcvt
#endif
