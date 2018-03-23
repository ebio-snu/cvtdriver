# 샘플드라이버

본 프로젝트에서는 두가지 종류의 샘플드라이버를 제공한다. 하나는 DSSampleDriver이고, 다른하나는 SSSampleDriver 이다. DSSampleDriver 는 스마트팜 장비와 직접 통신을 위한 DSDriver의 예로 제공되는 샘플이고, SSSampleDriver 는 스마트팜 장비를 핸들링할 소프트웨어와의 통신을 위한 SSDriver의 예로 제공된다.

## DSSampleDriver
 [소스코드](sample/dssampledriver.cpp)에 구현되어 있다. 컨버터와 함께 제공되는 샘플 노드와 통신을 수행한다. 샘플노드는 시리얼 통신을 통해 컨버터와 통신을 한다. 통신프로토콜과 관련된 내용은 샘플노드의 [프로토콜](https://github.com/ebio-snu/stdcvt/blob/master/doc/samplenode_protocol.md)을 참고한다.

 다수의 센서와 구동기를 다루는 예로 구현되었다. RS232 혹은 RS485 등의 통신방법을 사용하고 제조사별 프로토콜을 가지고 있다면 이 샘플을 참고하면 쉽게 드라이버 개발이 가능할 것이다.

## SSSampleDriver
 [소스코드](sample/sssampledriver.cpp)에 구현되어 있다. 테스트용 UI와 함께 동작하는 것으로 목표로 개발되었다. 테스트용 UI 와 데이터를 공유하기 위해 mysql을 사용한다. 샘플로 제공되는 드라이버이기 때문에 디비를 사용하지만 스키마는 아래와 같이 간단하다. 

```
create table devices (
    id varchar(30),
    devtype integer,
    section long,
    target integer,
    status integer,
    value float,
    unit integer
);

create table commands (
    id integer primary key,
    devtype integer,
    section long,
    target integer,
    onoff integer,
    ratio float
);
```

