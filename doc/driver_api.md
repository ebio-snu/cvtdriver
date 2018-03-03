# 드라이버 API

드라이버는 크게 2종류로 구분된다. 센서노드, 제어노드, 컨트롤러와 직접 연결되는 장비측(Device Side)드라이버와 데이터 수집기와 연결되는 서버측(Servier Side)드라이버로 구성된다. 각 드라이버를 DSDriver, SSDriver 라고 한다.

드라이버 API는 기초연동용과 고급연동용으로 구분될 계획이다. 현 단계에서 드라이버는 현상황을 충실히 포함하는쪽으로 설계하는 것을 목표로 하고 있다. 추후에 활성화가 되어 추상화 레벨을 높여서 더 많은 범위를 커버할 수 있기를 바란다.

## 드라이버 스펙 문서
현 시점에서 기초 연동을 위한 API 초안이 개발되어 있으며, 참여사와의 워크샵을 통해 기초 연동용 최종안이 개발될 것으로 기대된다.

드라이버 개발을 위해서 [CvtDriver 레퍼런스](https://ebio-snu.github.io/cvtdriver/)를 참고한다.

## 드라이버가 가진 장비 데이터의 공유
2개 이상의 DSDriver를 사용하는 경우 개별 DSDriver는 서로 다른 장비를 관리해야한다. 하나의 DSDriver에서 관리되는 장비에 대한 정보는 다른 장비로 전달될 수 있다. 

드라이버로부터 장비 정보를 획득하기 위해서는 CvtDevice *getdevice(int index); 메소드를 활용한다. index는 0부터 시작하고, 값을 하나씩 올려가면서 장비를 꺼낼 수 있다. 이때 리턴값이 nullptr(NULL)인 경우 관리하는 장비가 더이상 없다는 의미이다.

장비의 정보를 다른 드라이버로 전달하기 위해서 bool sharedevice(CvtDevice *pdevice); 메소드를 활용한다.

## 다른 드라이버로 제어명령 전달
장비에 대한 명령도 다른 드라이버로 전달될 수 있다. 다만 초기버전에서는 SSDriver가 하나만 존재하고, SSDriver에서만 명령을 전달할 수 있는 것으로한다.

하나의 드라이버(SSDriver)가 전달하고자 하는 명령은 CvtCommand *getcommand(int index); 메소드를 이용해 얻을 수 있다. index는 0부터 시작하고, 값을 하나씩 올려가면서 명령을 꺼낼 수 있다. 이때 리턴값이 nullptr(NULL)인 경우 더이상의 명령이 없다는 의미이다.

획득한 명령을 다른 드라이버로 전달하기 위해서 bool control(CvtCommand *pcmd); 메소드를 활용한다.

## 드라이버 설정
드라이버의 설정은 conf/cvtdriver.json 에 기록되어 있다. 설정파일은 ssdriver 와 dsdriver 로 나뉘어지는데 기본적인 구조는 동일하다.

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
            "baudrate": 115200
        }
    }]
}
```

하나의 드라이버에 대한 설정은 드라이버 파일명("driver")과 해당 드라이버 구동을 위한 옵션("option")으로 구성된다. 드라이버 파일명은 추후 협회의 시스템이 구축될때 내부적인 규칙에 따라 정리될 예정이다. 드라이버의 옵션은 해당드라이버에 맞게 개발자가 설정하면 된다.

위에서 SSSampleDriver 는 파일에 정보를 기록하고, 파일로부터 명령을 읽는 구조를 가지고 있어 해당 파일명들이 옵션에 기록되고, DSSampleDriver는 시리얼 통신을 통해 샘플노드와 통신을 하는 드라이버이기 때문에 옵션으로 port와  baudrate를 가지고 있다.

