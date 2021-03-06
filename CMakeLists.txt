#
# Copyright © 2018 ebio lab. SNU. All Rights Reserved.
#
# @file CmakeList.txt
# @date 2018-02-27, JoonYong
# @author Kim, JoonYong <tombraid@snu.ac.kr>
#
# This file is for compiling two sample drivers.
# refer from: https://github.com/ebio-snu/cvtdriver
#

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (cvtdriver)

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
SET(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/../doc/doxy.conf
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
ENDIF(DOXYGEN_FOUND)

FIND_PACKAGE(Boost 1.62 REQUIRED COMPONENTS system date_time filesystem iostreams)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

FIND_PACKAGE(Glog REQUIRED)
IF(GLOG_FOUND)
    INCLUDE_DIRECTORIES (${GLOG_INCLUDE_DIRS})
ENDIF(GLOG_FOUND)

ADD_DEFINITIONS(-fsigned-char -Wall) 

SET (LIBRARY_OUTPUT_PATH ../lib)

SET (CODEDICSRC ${CMAKE_CURRENT_BINARY_DIR}/cvtcodedic.cpp)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CODEDICSRC}
    COMMAND scripts/code.sh ${CODEDICSRC}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "=================== Generating ${CODEDICSRC} ======================" 
)

INCLUDE_DIRECTORIES (include spec)

SET (ALLSRC sample/dssampledriver.cpp sample/sssampledriver.cpp)

ADD_LIBRARY (dssample SHARED sample/dssampledriver.cpp ${CODEDICSRC})
TARGET_LINK_LIBRARIES(dssample ${Boost_LIBRARIES} ${GLOG_LIBRARIES} pthread)
ADD_LIBRARY (sssample SHARED sample/sssampledriver.cpp ${CODEDICSRC})
TARGET_LINK_LIBRARIES(sssample ${Boost_LIBRARIES} ${GLOG_LIBRARIES} pthread mysqlcppconn)

ENABLE_TESTING ()

ADD_EXECUTABLE (test_so_load test/test_so_load.cpp)
TARGET_LINK_LIBRARIES (test_so_load ${Boost_LIBRARIES} ${GLOG_LIBRARIES} pthread dl ${GTEST_LIBRARIES})

SET (TESTSRC asio;multi_device;actuator;motor)

foreach(TNAME ${TESTSRC}) 
    ADD_EXECUTABLE (test_${TNAME} test/test.cpp test/test_${TNAME}.cpp)
    TARGET_LINK_LIBRARIES (test_${TNAME} ${Boost_LIBRARIES} ${GLOG_LIBRARIES} pthread dl ${GTEST_LIBRARIES})
endforeach()

ADD_TEST (dstest_0 test_so_load dsdriver)
ADD_TEST (dstest_1 test_asio dsdriver)
ADD_TEST (dstest_2 test_multi_device dsdriver)
ADD_TEST (dstest_3 test_actuator dsdriver)
ADD_TEST (dstest_4 test_motor dsdriver)

ADD_TEST (sstest_0 test_so_load ssdriver)
#ADD_TEST (sstest_1 test_asio ssdriver)         # ssdriver 는 시리얼 통신을 수행하지 않음
ADD_TEST (sstest_2 test_multi_device ssdriver)
#ADD_TEST (sstest_3 test_actuator ssdriver)     # ssdriver 는 명령을 처리하지 않음.
#ADD_TEST (sstest_4 test_motor ssdriver)        # ssdriver 는 명령을 처리하지 않음.
