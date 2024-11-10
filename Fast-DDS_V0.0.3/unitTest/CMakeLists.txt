cmake_minimum_required(VERSION 3.10)  
project(MyProject)  
  
# 指定 C++ 标准  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  

add_definitions(-D__LITTLE_ENDIAN__)
  
# 包含头文件目录  
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/eprosimartps
)  
  

  
# 添加一个动态库  
add_executable(
    test 
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ertps/test_CacheChangePool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ertps/test_CDRMessage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ertps/test_HistoryCache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ertps/test_Participant.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ertps/common/test_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ertps/dds/test_DomainParticipant.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest/gtest-all.cc
)  
  

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
target_link_directories(test PRIVATE 
-lfastrtps)


# 如果需要，可以设置库的输出目录（可选）  
set_target_properties(
    test  
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/lib
)