#!/bin/bash

echo $1

echo "
// 이 파일은 자동으로 생성되는 파일입니다.
// 수작업으로 수정하시면 추후 작업내용이 삭제될 수 있습니다.
#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace stdcvt {

map<string, long> _codedic = { " > $1

grep -E '=' ../spec/cvtcode.h | tr -d ',' | awk '{print "{\""$1"\", "$3"},"}' >> $1
grep ' DL_' ../spec/cvtcode.h | awk '{print "{\""$2"\","$3"},"}' >> $1

echo "{\"\", 0}
};
}
" >> $1


