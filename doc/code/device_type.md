# 장비 종류

장비종류는 devtype_t 로 표현된다. 장비종류는 크게 5자리 unsigned int로 구분되는데, 장비의 분류 (1자리), 장비종류(2자리), 장비하위구분(2자리)로 구성된다. 장비하위구분은 구동기의 경우에 많이 보이는데, 온실의 측창이나 천창이 다중창인 경우가 대표적인 예라고 할 수 있다.

작명법은 센서의 경우 DT_SEN 으로 시작하고, 모터형 구동기의 경우 DT_MOT 로, 스위치형 구동기의 경우 DT_SWC로 시작한다. 이후의 명칭은 장비가 작동하는 대상이 된다. 온도센서의 경우 DT_SEN_TEMPERATURE, 측창의 경우 DT_MOT_SIDEWINDOW 가 된다.

아래의 센서종류는 [TTAK.KO-10.0903](http:///www.tta.or.kr/data/ttas_view.jsp?rn=1&pk_num=TTAK.KO-10.0903) 을 참고하여 작성되었다.

| 이름 | 분류번호 | 번호 | 분류 | 장비 | 설명 |
|:--------|--------:|:--------:|:--------:|--------:|:--------|
| DT_DEV_UNKNOWN | 0 | 0 | 기타장비 | 알수없는 장비 | 코드에 없는 장비인 경우. |
| DT_SEN_TEMPERATURE | 1 | 10100 | 센서 | 온도센서 | 온도를 측정하는 센서. |
| DT_SEN_HUMIDITY | 1 | 10200 | 센서 | 습도센서 | 습도를 측정하는 센서. |
| DT_SEN_RADIATION | 1 | 10300 | 센서 | 일사센서 | 일사량을 측정하는 센서. |
| DT_SEN_WINDDIRECTION | 1 | 10400 | 센서 | 풍향센서 | 풍향을 측정하는 센서. |
| DT_SEN_WINDSPEED | 1 | 10500 | 센서 | 풍속센서 | 풍속을 측정하는 센서. |
| DT_SEN_RAIN | 1 | 10600 | 센서 | 감우센서 | 비가 오는지 측정하는 센서. |
| DT_SEN_RAINFALL | 1 | 10700 | 센서 | 강우량센서 | 강우량을 측정하는 센서. |
| DT_SEN_PHOTONFLUX | 1 | 10800 | 센서 | PAR센서 | 유효광량을 측정하는 센서. |
| DT_SEN_SOILMOISTURE | 1 | 10900 | 센서 | 토양함수율센서 | 토양 함수율을 측정하는 센서. |
| DT_SEN_SOILMOISTURETENSION | 1 | 11000 | 토양수분장력센서 |  토양수분장력을 측정하는 센서. |
| DT_SEN_EC | 1 | 11100 | 센서 | EC센서 | EC를 측정하는 센서. |
| DT_SEN_PH | 1 | 11200 | 센서 | pH센서 | pH를 측정하는 센서. |
| DT_SEN_BATTERY | 1 | 11300 | 센서 | 배터리센서 | 배터리의 상태를 확인하는 센서. |
| DT_SEN_ADC | 1 | 11400 | 센서 | ADC | 센서는 아니지만 아날로그값을 디지털로 전환한 상태의 값을 전달. |
| DT_SEN_UNKNOWN | 1 | 19000 | 센서 | 알수없는 센서 | 코드에 없는 센서인 경우. |
| DT_MOT_SIDEWINDOW | 2 | 20100 | 모터형 구동기 | 측창 구동기 | 측창을 구동하는 모터형 구동기. |
| DT_MOT_SIDEWINDOW_1 | 2 | 20101 | 모터형 구동기 | 1중 측창 구동기 | 측창을 구동하는 모터형 구동기. |
| DT_MOT_SIDEWINDOW_2 | 2 | 20102 | 모터형 구동기 | 2중 측창 구동기 | 측창을 구동하는 모터형 구동기. |
| DT_MOT_SIDEWINDOW_3 | 2 | 20103 | 모터형 구동기 | 3중 측창 구동기 | 측창을 구동하는 모터형 구동기. |
| DT_MOT_SIDEWINDOW_4 | 2 | 20104 | 모터형 구동기 | 4중 측창 구동기 | 측창을 구동하는 모터형 구동기. |
| DT_MOT_SIDEWINDOW_5 | 2 | 20105 | 모터형 구동기 | 5중 측창 구동기 | 측창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFWINDOW | 2 | 20200 | 모터형 구동기 | 천창 구동기 | 천창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFWINDOW_1 | 2 | 20201 | 모터형 구동기 | 1중 천창 구동기 | 천창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFWINDOW_2 | 2 | 20202 | 모터형 구동기 | 2중 천창 구동기 | 천창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFWINDOW_3 | 2 | 20203 | 모터형 구동기 | 3중 천창 구동기 | 천창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFWINDOW_4 | 2 | 20204 | 모터형 구동기 | 4중 천창 구동기 | 천창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFWINDOW_5 | 2 | 20205 | 모터형 구동기 | 5중 천창 구동기 | 천창을 구동하는 모터형 구동기. |
| DT_MOT_ROOFCURTAIN | 2 | 20400 | 모터형 구동기 | 천장보온커튼 구동기 | 천장보온커튼을 구동하는 모터형 구동기. |
| DT_MOT_SIDECURTAIN | 2 | 20500 | 모터형 구동기 | 측면보온커튼 구동기 | 측면보온커튼을 구동하는 모터형 구동기. |
| DT_MOT_SHADINGCURTAIN | 2 | 20600 | 모터형 구동기 | 차광커튼 구동기 | 차광커튼을 구동하는 모터형 구동기. |
| DT_MOT_UNKNOWN | 2 | 29000 | 모터형 구동기 | 알수없는 모터형 구동기 | 코드에 없는 모터형 구동기인 경우. |
| DT_SWC_FAN | 3 | 30100 | 스위치형 구동기 | 팬 | 팬 |
| DT_SWC_FLOWFAN | 3 | 30101 | 스위치형 구동기 | 유동팬 | 내부 공기 유동을 위한 팬 |
| DT_SWC_VENTFAN | 3 | 30102 | 스위치형 구동기 | 환기팬 | 환기를 위한 팬 |
| DT_SWC_UNKNOWN | 3 | 39000 | 스위치형 구동기 | 알수없는 스위치형 구동기 | 코드에 없는 스위치형 구동기인 경우. |

알수없는 센서, 구동기, 장비의 경우 9000 번 이후의 번호는 개별 구현에서 충돌하지 않도록 사용할 수 있다. 이 경우 개발사 번호와 매칭시켜서 판단한다.

```
typedef enum {
  DG_UNKNOWN = 0,       ///< 알수없는 장비그룹
  DG_SENSOR = 1,        ///< 센서 그룹
  DG_MOTOR = 2,         ///< 모터형 구동기 그룹
  DG_SWITCH = 3,        ///< 스위치형 구동기 그룹
} devgroup_t;

typedef enum {
  DT_DEV_UNKNOWN = 0, ///< 알수없는 장비
  DT_SEN_TEMPERATURE = 10100, ///< 온도센서
  DT_SEN_HUMIDITY = 10200, ///< 습도센서
  DT_SEN_RADIATION = 10300, ///< 일사센서
  DT_SEN_WINDDIRECTION = 10400, ///< 풍향센서
  DT_SEN_WINDSPEED = 10500, ///< 풍속센서 
  DT_SEN_RAIN = 10600, ///< 감우센서 
  DT_SEN_RAINFALL = 10700, ///< 강우량센서 
  DT_SEN_PHOTONFLUX = 10800, ///< PAR센서 
  DT_SEN_SOILMOISTURE = 10900, ///< 토양함수율센서 
  DT_SEN_SOILMOISTURETENSION = 11000, ///< 토양수분장력센서 
  DT_SEN_EC = 11100, ///< EC센서 
  DT_SEN_PH = 11200, ///< pH센서
  DT_SEN_BATTERY = 11300, ///< 배터리센서
  DT_SEN_ADC = 11400, ///< ADC 변환된 Raw값 센서(?)
  DT_SEN_UNKNOWN = 19000, ///< 알수없는 센서 
  DT_MOT_SIDEWINDOW = 20100, ///< 측창 구동기 
  DT_MOT_SIDEWINDOW_1 = 20101, ///< 1중 측창 구동기 
  DT_MOT_SIDEWINDOW_2 = 20102, ///< 2중 측창 구동기 
  DT_MOT_SIDEWINDOW_3 = 20103, ///< 3중 측창 구동기 
  DT_MOT_SIDEWINDOW_4 = 20104, ///< 4중 측창 구동기 
  DT_MOT_SIDEWINDOW_5 = 20105, ///< 5중 측창 구동기 
  DT_MOT_ROOFWINDOW = 20200, ///< 천창 구동기 
  DT_MOT_ROOFWINDOW_1 = 20201, ///< 1중 천창 구동기 
  DT_MOT_ROOFWINDOW_2 = 20202, ///< 2중 천창 구동기 
  DT_MOT_ROOFWINDOW_3 = 20203, ///< 3중 천창 구동기 
  DT_MOT_ROOFWINDOW_4 = 20204, ///< 4중 천창 구동기 
  DT_MOT_ROOFWINDOW_5 = 20205, ///< 5중 천창 구동기 
  DT_MOT_ROOFCURTAIN = 20400, ///< 천장보온커튼 구동기 
  DT_MOT_SIDECURTAIN = 20500, ///< 측면보온커튼 구동기 
  DT_MOT_SHADINGCURTAIN = 20600, ///< 차광커튼 구동기 
  DT_MOT_UNKNOWN = 29000, ///< 알수없는 모터형 구동기
  DT_SWC_FAN = 30100, ///< 팬 
  DT_SWC_FLOWFAN = 30101, ///< 유동팬 
  DT_SWC_VENTFAN = 30102, ///< 환기팬 
  DT_SWC_UNKNOWN = 39000, ///< 알수없는 스위치형 구동기 
} devtype_t;
```
