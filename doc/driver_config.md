# 드라이버 설정 

드라이버의 설정은 conf/cvtdriver.json 에 기록되어 있다. 설정파일은 ssdriver 와 dsdriver 로 나뉘어지는데 기본적인 구조는 동일하다. ssdriver 와 dsdriver 모두 배열로 구성되어 있지만 실제로 ssdriver는 이번 버전에서는 하나의 아이템만이 의미가 있다. dsdriver는 여러개의 아이템을 사용할 수 있다.

## 드라이버 설정 예시
```
{
    "ssdriver": [{
        "driver": "libsssample.so",
        "option": {
            "host": "tcp://127.0.0.1:3306",
            "user": "ssdriver",
            "pass": "sssample",
            "db": "sssample"
        }
    }],
    "dsdriver": [{
        "driver": "libdssample.so",
        "option": {
            "port": "/dev/ttyUSB0",
            "baudrate": 115200
        }
    }]
}
```

## 개별 드라이버 설정
개별 드라이버에 대한 설정은 드라이버 파일명("driver")과 해당 드라이버 구동을 위한 옵션("option")으로 구성된다. 드라이버 파일명은 추후 협회의 시스템이 구축될때 내부적인 규칙에 따라 정리될 예정이다. 드라이버의 옵션은 해당드라이버에 맞게 개발자가 설정하면 된다.

위에서 ssdriver는 파일에 정보를 기록하고, 파일로부터 명령을 읽는 구조를 가지고 있어 해당 파일명들이 옵션에 기록되고, dsdriver는 시리얼 통신을 통해 샘플노드와 통신을 하는 드라이버이기 때문에 옵션으로 port와 baudrate를 가지고 있다.

## 장비스펙을 반영한 설정
장비 스펙을 설정하기 위해서 [코드테이블](code_table.md)을 이해하는 것이 중요하다. 코드테이블을 이해하더라도 실제 제조사의 제품에 장비 스펙에 대한 기록이 없는 경우 동적으로 이를 반영하는 것이 어렵다. 이런 경우 쉽게 장비스펙을 반영하기 위한 옵션을 제공한다. 아래의 예에서 dsdriver의 option을 보면, _sensors, _motors, _switches 가 있는 것을 확인할 수 있다. 이렇게 옵션을 넣어두는 경우 CvtDeviceFactory를 사용해서 쉽게 장비스펙을 반영한 장비를 생성할 수 있다.

```
{
  "ssdriver": [{
    "driver": "libsssample.so",
    "option": {
      "value": "value.json",
      "command": "command.json"
    }
  }],
  "dsdriver": [{
    "driver": "libdssample.so",
    "option": {
      "port": "/dev/ttyUSB0",
      "baudrate": 115200,
      "_sensors" : [{
        "id" : "10",
        "type" : "DT_SEN_HUMIDITY",
        "section" : "DL_DEFAULT_PLANTZONE",
        "target" : "DO_ENV_ATMOSPHERE",
        "status" : "DS_SEN_NORMAL",
        "unit" : "OU_PERCENT"
      }, {
        "id" : "11",
        "type" : "DT_SEN_TEMPERATURE",
        "section" : "DL_DEFAULT_PLANTZONE",
        "target" : "DO_ENV_ATMOSPHERE",
        "status" : "DS_SEN_NORMAL",
        "unit" : "OU_CELSIUS"
      }],
      "_switches" : [{
        "id" : "30",
        "type" : "DT_SWC_FAN",
        "section" : "DL_DEFAULT_PLANTZONE",
        "target" : "DO_EQUIPMENT",
        "status" : "DS_SWC_OFF"
      }, {
        "id" : "31",
        "type" : "DT_SWC_FAN",
        "section" : "DL_DEFAULT_PLANTZONE",
        "target" : "DO_EQUIPMENT",
        "status" : "DS_SWC_OFF"
      }],
      "_motors" : [{
        "id" : "20",
        "type" : "DT_MOT_SIDEWINDOW",
        "section" : "DL_DEFAULT_PLANTZONE",
        "target" : "DO_EQUIPMENT",
        "status" : "DS_MOT_STOP"
      }, {
        "id" : "21",
        "type" : "DT_MOT_SIDEWINDOW",
        "section" : "DL_DEFAULT_PLANTZONE",
        "target" : "DO_EQUIPMENT",
        "status" : "DS_MOT_STOP"
      }]
    }
  }]
}
```
