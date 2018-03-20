# CMake generated Testfile for 
# Source directory: /home/tombraid/Works/ebio/cvtdriver
# Build directory: /home/tombraid/Works/ebio/cvtdriver/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(dstest_0 "test_so_load" "dsdriver")
add_test(dstest_1 "test_asio" "dsdriver")
add_test(dstest_2 "test_multi_device" "dsdriver")
add_test(dstest_3 "test_actuator" "dsdriver")
add_test(dstest_4 "test_motor" "dsdriver")
add_test(sstest_0 "test_so_load" "ssdriver")
add_test(sstest_2 "test_multi_device" "ssdriver")
