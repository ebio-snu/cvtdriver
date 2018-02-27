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

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
	ADD_CUSTOM_TARGET(doc
		${DOXYGEN_EXECUTABLE} doc.src/doxy.conf
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
ENDIF(DOXYGEN_FOUND)

FIND_PACKAGE(Boost 1.62 REQUIRED COMPONENTS date_time filesystem iostreams)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

FIND_PACKAGE(Glog REQUIRED)
IF(GLOG_FOUND)
    INCLUDE_DIRECTORIES (${GLOG_INCLUDE_DIRS})
ENDIF(GLOG_FOUND)

FIND_PACKAGE(GTest REQUIRED)
IF(GTEST_FOUND)
    INCLUDE_DIRECTORIES (${GTEST_INCLUDE_DIRS})
ENDIF(GTEST_FOUND)

ADD_DEFINITIONS(-fsigned-char -Wall) 

SET (LIBRARY_OUTPUT_PATH ../lib)

INCLUDE_DIRECTORIES (spec)

ADD_LIBRARY (dssample SHARED sample/dssample.cpp)
TARGET_LINK_LIBRARIES(dssample ${Boost_LIBRARIES})
ADD_LIBRARY (sssample SHARED sample/sssample.cpp)
TARGET_LINK_LIBRARIES(sssample ${Boost_LIBRARIES})

ENABLE_TESTING ()

ADD_EXECUTABLE (test_level_0 test/test_level_0.cpp)
ADD_EXECUTABLE (test_level_1 test/test_level_1.cpp)

ADD_TEST (dstest_0 test_level_0 dssample)
ADD_TEST (dstest_1 test_level_1 dssample)

ADD_TEST (sstest_0 test_level_0 sssample)
ADD_TEST (sstest_1 test_level_1 sssample)
