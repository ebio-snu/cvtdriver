/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtcode.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file has various common codes.
 refer from: https:///github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_CODE_
#define _CVT_CODE_

#define CVT_OPTION_ASIO_SERVICE     "opt_asio_service"    ///< boost::asio::io_service 를 위한 옵션 키

namespace stdcvt {
    /** 장비 설치 구역 타입 */
    typedef long devsec_t;

#define DL_UNKOWN               -2              ///< 설치구역 알수 없음
#define DL_OUTSIDE              -1              ///< 설치구역 외부
#define DL_DEFAULT_ROOTZONE     10103010101     ///< 디폴트 설치구역 지하부
#define DL_DEFAULT_PLANTZONE    10103010102     ///< 디폴트 설치구역 작물부
#define DL_DEFAULT_ROOFZONE     10103010103     ///< 디폴드 설치구역 작물상부


    /** 장비 상태 타입 */
    typedef enum {
        DS_DEV_ABNORMAL = 1,    ///< 비정상
        DS_SEN_NORMAL = 101,    ///< 센서 정상 상태
        DS_SWC_ON = 201,        ///< 스위치 켜짐(정상)
        DS_SWC_OFF = 202,       ///< 스위치 꺼짐(정상)
        DS_MOT_OPEN = 301,      ///< 모터 열리는 중(정상)
        DS_MOT_CLOSE = 302,     ///< 모터 닫히는 중(정상)
        DS_MOT_STOP = 303       ///< 모터 중지상태(정상)
    } devstat_t;

    /** 장비 작동대상 타입 */
    typedef enum {
        DO_UNKNOWN = 1,                 ///< 대상을 알지 못함
        DO_ENV_ATMOSPHERE = 1001,       ///< 대기를 대상으로 함
        DO_ENV_SOIL = 1002,             ///< 토양을 대상으로 함
        DO_ENV_NUTRIENTSOLUTION = 1003, ///< 양액을 대상으로 함
        DO_PLANT_STEM = 2001,           ///< 작물의 줄기를 대상으로 함
        DO_PLANT_LEAF = 2002,           ///< 작물의 잎을 대상으로 함
        DO_PLANT_FRUIT = 2003,          ///< 작물의 과실을 대상으로 함
        DO_PLANT_ROOT = 2004,           ///< 작물의 뿌리를 대상으로 함
        DO_EQUIPMENT = 3001,            ///< 농장의 장비를 대상으로 함
        DO_EQUIPMENT_NORTH = 3002,      ///< 농장의 장비가 좌우대칭인 경우 북쪽에 가까운 장비를 대상으로 함
        DO_EQUIPMENT_SOUTH = 3003       ///< 농장의 장비가 좌우대칭인 경우 남쪽에 가까운 장비를 대상으로 함
    } devtarget_t;

    /** 장비 그룹 타입 */
    typedef enum {
        DG_UNKNOWN = 0,       ///< 알수없는 장비그룹
        DG_SENSOR = 1,        ///< 센서 그룹
        DG_MOTOR = 2,         ///< 모터형 구동기 그룹
        DG_SWITCH = 3,        ///< 스위치형 구동기 그룹
    } devgroup_t;

    /** 장비 종류 타입 */
    typedef enum {
        DT_DEV_UNKNOWN = 0,             ///< 알수없는 장비 
        DT_SEN_TEMPERATURE = 10100,     ///< 온도센서
        DT_SEN_HUMIDITY = 10200,        ///< 습도센서
        DT_SEN_RADIATION = 10300,       ///< 일사센서
        DT_SEN_WINDDIRECTION = 10400,   ///< 풍향센서
        DT_SEN_WINDSPEED = 10500,       ///< 풍속센서  
        DT_SEN_RAIN = 10600,            ///< 감우센서  
        DT_SEN_RAINFALL = 10700,        ///< 강우량센서  
        DT_SEN_PHOTONFLUX = 10800,      ///< PAR센서  
        DT_SEN_SOILMOISTURE = 10900,    ///< 토양함수율센서  
        DT_SEN_SOILMOISTURETENSION = 11000, ///< 토양수분장력센서  
        DT_SEN_EC = 11100,              ///< EC센서  
        DT_SEN_PH = 11200,              ///< pH센서
        DT_SEN_BATTERY = 11300,         ///< 배터리센서
        DT_SEN_ADC = 11400,             ///< ADC 변환된 Raw값 센서(?)
        DT_SEN_UNKNOWN = 19000,         ///< 알수없는 센서  
        DT_MOT_SIDEWINDOW = 20100,      ///< 측창 구동기  
        DT_MOT_SIDEWINDOW_1 = 20101,    ///< 1중 측창 구동기  
        DT_MOT_SIDEWINDOW_2 = 20102,    ///< 2중 측창 구동기  
        DT_MOT_SIDEWINDOW_3 = 20103,    ///< 3중 측창 구동기  
        DT_MOT_SIDEWINDOW_4 = 20104,    ///< 4중 측창 구동기  
        DT_MOT_SIDEWINDOW_5 = 20105,    ///< 5중 측창 구동기  
        DT_MOT_ROOFWINDOW = 20200,      ///< 천창 구동기  
        DT_MOT_ROOFWINDOW_1 = 20201,    ///< 1중 천창 구동기  
        DT_MOT_ROOFWINDOW_2 = 20202,    ///< 2중 천창 구동기  
        DT_MOT_ROOFWINDOW_3 = 20203,    ///< 3중 천창 구동기  
        DT_MOT_ROOFWINDOW_4 = 20204,    ///< 4중 천창 구동기  
        DT_MOT_ROOFWINDOW_5 = 20205,    ///< 5중 천창 구동기
        DT_MOT_ROOFCURTAIN = 20400,     ///< 천장보온커튼 구동기
        DT_MOT_SIDECURTAIN = 20500,     ///< 측면보온커튼 구동기
        DT_MOT_SHADINGCURTAIN = 20600,  ///< 차광커튼 구동기
        DT_MOT_UNKNOWN = 29000,         ///< 알수없는 모터형 구동기
        DT_SWC_FAN = 30100,             ///< 팬
        DT_SWC_FLOWFAN = 30101,         ///< 유동팬
        DT_SWC_VENTFAN = 30102,         ///< 환기팬
        DT_SWC_UNKNOWN = 39000,         ///< 알수없는 스위치형 구동기
    } devtype_t;

    /** 센서 관측치 단위 타입*/
    typedef enum {
        OU_NONE = 1,        ///< 단위가 없는 무차원 값  
        OU_CELSIUS = 2,     ///< ℃ 
        OU_PERCENT = 3,     ///< % 
        OU_PPM = 4,         ///< ppm 
        OU_W_PER_MSQ = 5,   ///< W/㎡
        OU_DEGREE = 6,      ///< ° 
        OU_M_PER_SEC = 7,   ///< m/s 
        OU_MMOL_PER_MSQSEC = 8, ///< μmol/㎡/s 
        OU_KPA = 9,         ///< kPa 
        OU_DS_PER_M = 10,   ///< dS/m 
        OU_PH = 11,         ///< pH 
    } obsunit_t;

}

#endif

