# cvtdriver
컨버터 스펙을 기준으로 드라이버 개발을 돕기위한 저장소

## 소개
본 저장소는 [스마트팜 기기 연동을 위한 컨버터](https://github.com/ebio-snu/stdcvt)에서 활용될 수 있는 드라이버의 스펙과 샘플 드라이버를 제공하여 참여사의 드라이버 제작을 돕기위한 것이다.

## 드라이버 API 스펙

드라이버는 크게 2종류로 구분된다. 센서노드, 제어노드, 컨트롤러와 직접 연결되는 장비측(Device Side)드라이버와 데이터 수집기와 연결되는 서버측(Servier Side)드라이버로 구성된다. 각 드라이버를 DSDriver, SSDriver 라고 한다.

드라이버 API는 기초연동용과 고급연동용으로 구분될 계획이다. 현 단계에서 드라이버는 현상황을 충실히 포함
하는쪽으로 설계하는 것을 목표로 하고 있다. 추후에 활성화가 되어 추상화 레벨을 높여서 더 많은 범위를 커버할 수 있기를 바란다.

다음의 문서를 참고한다.
* [드라이버 API 설명](doc/driver_api.md)
* [드라이버에서 사용할 코드테이블](doc/code_table.md)
* [드라이버 API 스펙](https://ebio-snu.github.io/cvtdriver/)


## 사용법
### 소스 코드의 획득
```
sudo apt install git
git clone https://github.com/ebio-snu/cvtdriver.git
```

### 빌드를 위한 패키지 설치
```
sudo apt install build-essential cmake libgoogle-glog-dev libasio-dev libjansson-dev libboost-all-dev
```
boost.dll 은 1.61이후 버전부터 지원한다. Raspbian stretch를 사용하는 경우 libboost-all-dev는 1.62.0.1 버전이지만, jessie나 wheezy를 사용하는 경우에는 버전이 낮아서 1.61 이상의 소스를 받아서 설치해야 한다. 

### 소스코드 업데이트 및 빌드
```
cd cvtdriver
git pull
rm -rf build
mkdir build
cd build
cmake ..
make
```

### 샘플드라이버 테스트
```
make test
```

## 신규드라이버 개발시 테스트 방법

신규 드라이버를 개발하는 경우 코드를 공개할 의무가 없기 때문에 개발사에서 드라이버를 테스트 하는 것이 매우 중요하다.

test 폴더에는 드라이버 테스트를 위한 코드들이 들어있는데, 이 코드를 활용하면 신규 드라이버를 테스트할 수 있다. 
* test_so_load : 드라이버가 로딩되는지 테스트 한다.
* test_asio : asio::io_service 를 전달하여 이를 통한 통신이 진행되는지 테스트한다.
* 테스트가 추가되는데로 여기에 기록한다.

테스트 코드들은 설정파일을 기반으로 동작하기 때문에 /conf/cvtdriver.json 파일의 내용을 개발하는 드라이버의 정보로 변경한 뒤 make test 명령을 통해 신규 드라이버 테스트가 가능하다.


## 개발관련 공통사항
* 라이브러리
  * [google glog](https://github.com/google/glog) : Google 에서 공개한 로깅라이브러리
  * [jsoncons](https://danielaparker.github.io/jsoncons/) : JSON 라이브러리
  * [Boost](http://www.boost.org/) : [asio](https://think-async.com/)와 [dll](http://www.boost.org/doc/libs/1_65_1/doc/html/boost_dll.html)을 주로 사용
  * 개별 드라이버 개발을 위해 필요한 라이브러리를 사용할 수 있다.

* 개발환경
  * g++ : 기본 설정으로 g++을 사용. VC에서 테스트되지는 않았지만 큰 문제는 없을것으로 기대.
  * cmake : 빌드환경

* 개발문서
  * [doxygen](http://www.stack.nl/~dimitri/doxygen/) : 코드 문서화를 위해 활용
