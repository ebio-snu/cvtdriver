# 관측치 단위

관측치 단위는 obsunit_t 로 표현된다. 사용되는 모든 단위는 이 문서에 등록되어야 한다. 단위를 조합하여 사용하는 것은 불가능하다.

아래의 관측치 단위는 [TTAK.KO-10.0903](http://www.tta.or.kr/data/ttas_view.jsp?rn=1&pk_num=TTAK.KO-10.0903) 을 참고하여 작성되었다.

| 이름 | 번호 | 단위 | 설명 |
|:--------|--------:|:--------:|:--------|
| OU_NONE | 1 | |  단위가 없는 무차원 값 |
| OU_CELSIUS | 2 | ℃ |  섭씨온도단위 |
| OU_PERCENT | 3 | % | 퍼센트 |
| OU_PPM | 4 | ppm | 농도 |
| OU_W_PER_MSQ | 5 | W/㎡| 평방미터당 와트 |
| OU_DEGREE | 6 | ° | 각도 |
| OU_M_PER_SEC | 7 | m/s | 속도 |
| OU_MMOL_PER_MSQSEC | 8 | μmol/㎡/s | 유효광량 |
| OU_KPA | 9 | kPa | 압력(토양수분장력) |
| OU_DS_PER_M | 10 | dS/m | 전기전도도 |
| OU_PH | 11 | pH | 수소이온농도 | 

```
typedef enum {
  OU_NONE = 1, //< 단위가 없는 무차원 값 
  OU_CELSIUS = 2, //< ℃ 
  OU_PERCENT = 3, //< % 
  OU_PPM = 4, //< ppm 
  OU_W_PER_MSQ = 5, //< W/㎡
  OU_DEGREE = 6, //< ° 
  OU_M_PER_SEC = 7, //< m/s 
  OU_MMOL_PER_MSQSEC = 8, //< μmol/㎡/s 
  OU_KPA = 9, //< kPa 
  OU_DS_PER_M = 10, //< dS/m 
  OU_PH = 11, //< pH 
} obsunit_t;
```
