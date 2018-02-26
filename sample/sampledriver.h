/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file sampledriver.h
 @date 2018-02-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for sample driver.
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "../spec/cvtdriver.h"

using namespace stdcvt;

namespace sampledriver {

class SampleDriver : stdcvt::CvtDriver {
private:
    boost::asio::serial_port _port;
    char _buf[BUFSIZE];
    SampleSensor *_psensor;
    SampleMotor *_pmotor;
    SampleSwitch *_pswitch;

    void startread() {
        _port.async_read_until (asio::buffer(_buf, BUFSIZE), '\n',
            boost::bind(&serial::echo, this,
                asio::placeholders::error, asio::placeholders::bytes_transferred) );
    }

    void handlewrite(const asio::error_code& error, size_t bytes_transferred) {
        std::cout << bytes_transferred << " bytes, error: " << error << std::endl;
    }

    void readmessage (const asio::error_code& error, size_t bytes_transferred) {
        if (error || !bytes_transferred) {
            std::cout << "read nothing." << std::endl;
        } else {
            _buf[bytes_transferred]=0;
            // parse
        }
        startread ();
    }

public:
    /**
     새로운 드라이버를 생성한다.
     @param modelcode 모델코드
     @param apispec API 버전
    */
    SampleDriver(int modelcode, int apispec, asio::io_service& io) 
        : _port(io), stdcvt::CvtDriver (modelcode, apispec) {
    }

    ~SampleDriver () {
        finalize ();
    }

    /**
     드라이버 제작자가 부여하는 버전번호를 확인한다.
     @return 문자열 형식의 버전번호
    */
    string getversion () {
        return "V0.1.0";
    }

    /**
     드라이버 제작자가 부여하는 모델번호를 확인한다.
     @return 문자열 형식의 모델번호
    */
    string getmodel () {
        return "ebionode_v1";
    }

    /**
     드라이버 제조사명을 확인한다.
     컨버터에서는 제조사명을 로깅용도로만 사용한다.
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
    bool initialize (CvtConfig option) {
        _port.open (option.get("port"));
        _port.set_option (asio::serial_port_base::baud_rate(option.getint("baudrate")));

        startread ();
        return true;
    }

    /**
     드라이버를 종료한다.
     @return 종료 성공 여부
    */
    bool finalize () {
        psensor->finalize ();
        pmotor->finalize ();
        pswitch->finalize ();
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
        asio::async_write(_port, asio::buffer(_buf, strlen(_buf)),
                boost::bind(&serial::handle_write, this,
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));
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
                return psensor;
            case 1:
                return pmotor;
            case 2:
                return pswitch;
            default:
                return NULL;
        }
    }
};

extern "C" BOOST_SYMBOL_EXPORT sampledriver plugin;
sampledriver plugin;

} // namespace sampledriver
