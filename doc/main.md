Converting Driver for SmartFarm Devices             {#mainpage}
=======================================

# cvtdriver

cvtdriver 는 [스마트팜장비 연동을 위한 컨버터 개발](https://github.com/ebio-snu/stdcvt) 프로젝트에서 활용되는 드라이버개발을 돕기 위한 프로젝트이다. 본 프로젝트에서 드라이버 개발을 위한 API 스펙 및 샘플 드라이버를 제공하여 참여사의 드라이버 제작을 돕는다.

## 클래스 구조

드라이버 클래스 구조는 다음과 같다.

![class_diagram](https://raw.githubusercontent.com/ebio-snu/cvtdriver/master/doc/images/driver_class.png)

* [CvtDriver](@ref stdcvt::CvtDriver) : 드라이버의 인터페이스가 되는 가상 클래스이다. 
* [CvtOption](@ref stdcvt::CvtOption) : 드라이버 구동을 위한 옵션을 전달하는 클래스이다.
* [CvtDeviceSpec](@ref stdcvt::CvtDeviceSpec) : 드라이버에서 다루는 장비의 스펙을 다루는 클래스이다. 장비종류, 설치위치, 장비의 작동대상, 제조사, 모델명을 처리한다.
* [CvtDevice](@ref stdcvt::CvtDevice) : 드라이버에서 다루는 장비의 인터페이스가 되는 가상 클래스이다. 
  * [CvtSensor](@ref stdcvt::CvtSensor) : 센서의 인터페이스가 되는 클래스이다. 간단한 경우라면 직접 사용이 가능하다.
  * [CvtActuator](@ref stdcvt::CvtActuator) : 일반 구동기의 인터페이스가 되는 클래스이다. 스위치형 구동기에 사용하면 된다. 
  * [CvtMotor](@ref stdcvt::CvtMotor) : 모터형 구동기의 인터페이스가 되는 클래스로 CvtActuator를 상속한다. 간단한 경우라면 직접 사용이 가능하다. 
* [CvtCommand](@ref stdcvt::CvtCommand) : 구동기에서 처리하는 명령의 인터페이스가 되는 클래스이다.
  * [CvtRatioCommand](@ref stdcvt::CvtRatioCommand) : 구동기 전달하는 명령이 비율(퍼센트)인 경우에 사용하는 클래스이다. 모터형 구동기에 적합한 명령클래스라고 할 수 있다.


## 샘플 드라이버
두가지 종류의 샘플드라이버를 제공한다.

* [DSSampleDriver](@ref ebiodriver::DSSampleDriver) : 별도로 제공되는 샘플 노드와 serial 통신을 수행하는 드라이버이다. boost::asio 를 사용한다.

* [SSSampleDriver](@ref ebiodriver::SSSampleDriver) : 별도로 제공되는 테스트UI와 연동되는 드라이버이다. (현재는 구현이 안되어있다.)

