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
sudo apt install build-essential cmake libgoogle-glog-dev libasio-dev libjansson-dev
```

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

추후 업데이트될 예정입니다.


