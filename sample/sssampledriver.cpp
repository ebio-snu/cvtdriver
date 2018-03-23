/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file sssampledriver.cpp
 @date 2018-03-22, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for server-side sample driver.
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#include <iostream>
#include <sstream>
#include <string>
#include <queue>

#include <boost/config.hpp>

#include <glog/logging.h>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


#include "../spec/cvtdevice.h"
#include "../spec/cvtdriver.h"


using namespace std;
using namespace stdcvt;

namespace ebiodriver {

// 센서에 기능을 추가하고 싶을때 사용할 수 있다는 예시
// CvtSensor 는 id로 문자열을 처리하지만, SSSensor는 숫자로 처리함
// 실제로 사용하지는 않음
class SSSensor : public CvtSensor {
public:
    SSSensor(int devid, stdcvt::devtype_t devtype, stdcvt::devsec_t section,
        stdcvt::devtarget_t target, stdcvt::devstat_t devstatus, stdcvt::obsunit_t unit)
        : stdcvt::CvtSensor (to_string(devid), devtype, section, target, devstatus, unit) {
    }
};

// 모터에 기능을 추가하고 싶을때 사용할 수 있다는 예시
// CvtMotor 는 id로 문자열을 처리하지만, SSMotor는 숫자로 처리함
// 실제로 사용하지는 않음
class SSMotor : public CvtMotor{
public:
    SSMotor(int devid, stdcvt::devtype_t devtype, stdcvt::devsec_t section,
        stdcvt::devtarget_t target, stdcvt::devstat_t devstatus)
        : stdcvt::CvtMotor(to_string(devid), devtype, section, target, devstatus) {
    }
};

// 스위치에 기능을 추가하고 싶을때 사용할 수 있다는 예시
// CvtActuator는 id로 문자열을 처리하지만, SSSwitch는 숫자로 처리함
// 실제로 사용하지는 않음
class SSSwitch : public CvtActuator {
public:
    SSSwitch(int devid, stdcvt::devtype_t devtype, stdcvt::devsec_t section,
        stdcvt::devtarget_t target, stdcvt::devstat_t devstatus)
        : stdcvt::CvtActuator(to_string(devid), devtype, section, target, devstatus) {
    }
};

class SSSampleDriver : public CvtDriver {
private:
    int _lastcmdid;                 ///< 명령아이디 시퀀스
    queue<CvtCommand *> _cmdq;      ///< 명령 큐
    vector<CvtDevice *> _devvec;    ///< 디바이스 벡터
    string _host;                   ///< 디비 호스트
    string _user;                   ///< 디비 사용자
    string _pass;                   ///< 디비 사용자 암호
    string _db;                     ///< 디비명

    sql::Driver *_driver;           ///< 디비 드라이버
    sql::Connection *_con;          ///< 디비 연결자

public:
    /**
     새로운 SS드라이버를 생성한다.
    */
    SSSampleDriver() : stdcvt::CvtDriver (2001, 100) {
        _lastcmdid = 0;
        _host = _user = _pass = _db = "";
        updated(); // 샘플 SS드라이버는 직접 통신을 수행하지 않기 때문에, 테스트 통과를 위해서 넣음.
    }

    ~SSSampleDriver () {
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
        return "ebioss_v1";
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
    bool initialize (CvtOption option) {
        LOG(INFO) << "SSSampleDriver initialized.";
        _host = option.get("host");
        _user = option.get("user");
        _pass = option.get("pass");
        _db = option.get("db");

        try {
            _driver = get_driver_instance();
            _con = _driver->connect(_host, _user, _pass);
            _con->setSchema(_db);

        } catch (sql::SQLException &e) {
            LOG(ERROR) << "# ERR: SQLException " << e.what()
                       << " (MySQL error code: " << e.getErrorCode()
                       << ", SQLState: " << e.getSQLState() << " )";
            return false;
        }
        return true;
    }

    /**
     드라이버를 종료한다.
     @return 종료 성공 여부
    */
    bool finalize () {
        delete _con;
        LOG(INFO) << "SSSampleDriver finalized.";
        return true;
    }

    /**
     드라이버간 상태교환을 하기전에 호출되는 메소드로 전처리를 수행한다.
     @return 전처리 성공 여부
    */
    bool preprocess () {
        //read command from DB
        try {
            sql::Statement *stmt;
            sql::ResultSet *res;
            CvtCommand *pcmd;

            stmt = _con->createStatement();
            res = stmt->executeQuery("SELECT id, devtype, section, target, onoff, ratio from commands");
            while (res->next()) {
                if (CvtDevice::getgroup((devtype_t)res->getInt(2)) == DG_MOTOR) {
                    CvtDeviceSpec tmpspec((devtype_t)res->getInt(2), 
                            (devsec_t)res->getInt64(3), (devtarget_t)res->getInt(4));
                    pcmd = new CvtRatioCommand (res->getInt(1), &tmpspec, 
                            (res->getInt(5) > 0) ? true: false, res->getDouble(6));
                } else if (res->getInt(2) / 10000 == DG_SWITCH) {
                    CvtDeviceSpec tmpspec((devtype_t)res->getInt(2), 
                            (devsec_t)res->getInt64(3), (devtarget_t)res->getInt(4));
                    pcmd = new CvtCommand (res->getInt(1), &tmpspec, 
                                            res->getInt(5)>0? true: false);
                } else {
                    continue;
                }
                _cmdq.push (pcmd);
            }

            delete res;
            delete stmt;
        } catch (sql::SQLException &e) {
            LOG(ERROR) << "# ERR: SQLException " << e.what()
                       << " (MySQL error code: " << e.getErrorCode()
                       << ", SQLState: " << e.getSQLState() << " )";
            return false;
        } 

        updated(); // 샘플 SS드라이버는 직접 통신을 수행하지 않기 때문에, 테스트 통과를 위해서 넣음.
        return true;
    }

    /**
     드라이버간 상태교환이 이루어진 이후에 호출되는 메소드로 후처리를 수행한다.
     @return 후처리 성공 여부
    */
    bool postprocess () {
        //write observation to DB
        try {
            sql::Statement *stmt;
            sql::PreparedStatement  *prepstmt;

            stmt = _con->createStatement();
            stmt->executeQuery("TRUNCATE TABLE DEVICES");
            delete stmt;

            prepstmt = _con->prepareStatement(
                "INSERT INTO devices(id, devtype, section, target, status, value, unit)"
                "  VALUES (?, ?, ?, ?, ?, ?, ?)");

            for (vector<CvtDevice *>::size_type i = 0; i < _devvec.size(); ++i) {
                prepstmt->setString(1, _devvec[i]->getid());
                prepstmt->setInt(2, (_devvec[i]->getspec())->gettype());
                prepstmt->setInt64(3, (_devvec[i]->getspec())->getsection());
                prepstmt->setInt(4, (_devvec[i]->getspec())->gettarget());
                prepstmt->setInt(5, _devvec[i]->getstatus());
                if (CvtSensor *psensor = dynamic_cast<CvtSensor *>(_devvec[i])) {
                    prepstmt->setDouble(6, psensor->readobservation ());
                    prepstmt->setInt(7, psensor->getunit ());
                } else if (CvtActuator *pactuator = dynamic_cast<CvtActuator *>(_devvec[i])) {
                    prepstmt->setDouble(6, 0);
                    prepstmt->setInt(7, OU_NONE);
                } else if (CvtMotor *pmotor= dynamic_cast<CvtMotor *>(_devvec[i])) {
                    prepstmt->setDouble(6, pmotor->getcurrent ());
                    prepstmt->setInt(7, OU_NONE);
                }
                prepstmt->execute ();
                delete _devvec[i];
            }
            delete prepstmt;
            _devvec.clear ();

        } catch (sql::SQLException &e) {
            LOG(ERROR) << "# ERR: SQLException " << e.what()
                << " (MySQL error code: " << e.getErrorCode()
                << ", SQLState: " << e.getSQLState() << " )";
            return false;
        }
        return true;
    }

    /**
     드라이버가 관리하고 있는 장비의 포인터를 꺼내준다.
     @param index 얻고자 하는 장비의 인덱스 번호. 0에서 시작한다.
     @return 인덱스에 해당하는 장비의 포인터. NULL 이라면 이후에 장비가 없다는 의미이다.
    */
    CvtDevice *getdevice(int index) {
        return nullptr;
    }

    /**
      전달된 장비의 정보를 획득한다. 
      다른 드라이버의 장비정보를 입력해주기 위해 컨버터가 호출한다.
      @param pdevice 다른 드라이버의 장비 포인터
      @return 성공여부. 관심이 없는 장비인 경우라도 문제가 없으면 true를 리턴한다.
     */
    bool sharedevice(CvtDevice *pdevice) {
        CvtDevice *newdev = pdevice->clone ();
        _devvec.push_back (newdev);
        return true;
    }

    /**
      다른 드라이버가 관리하고 있는 장비를 제어하고자 할때 명령을 전달한다.
      명령을 전달하지 않는 드라이버라면 그냥 NULL을 리턴하도록 만들면 된다.
      @return 인덱스에 해당하는 명령의 포인터. NULL 이라면 이후에 명령이 없다는 의미이다.
     */
    CvtCommand *getcommand() {
        if (_cmdq.empty ())
            return nullptr;
        CvtCommand *pcmd = _cmdq.front();
        _cmdq.pop ();
        return pcmd;
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

extern "C" BOOST_SYMBOL_EXPORT SSSampleDriver plugin;
SSSampleDriver plugin;

} // namespace ebiodriver
