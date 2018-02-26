# cvtdriver
컨버터 스펙을 기준으로 드라이버 개발을 돕기위한 저장소

## 소개
본 저장소는 [스마트팜 기기 연동을 위한 컨버터](https://github.com/ebio-snu/stdcvt)에서 활용될 수 있는 드라이버의 스펙과 샘플 드라이버를 제공하여 참여사의 드라이버 제작을 돕기위한 것이다.

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

## 새로운 드라이버의 제작

새로운 드라이버 제작을 하는 경우, samples 폴더 중 하나의 샘플을 복사하여 시작하는 것을 추천한다.
개발한 드라이버는 다음과 같이 테스트한다. 모든 테스트를 통과하면 사용가능한 드라이버가 된다.

```
make driver_test {lib_new_driver_name.so}
```

상세한 내용은 추후 업데이트될 예정이다.


