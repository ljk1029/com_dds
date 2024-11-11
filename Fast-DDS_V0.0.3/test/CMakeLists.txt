cmake_minimum_required(VERSION 3.10)  
project(MyProject)  
  
# 指定 C++ 标准  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  

add_definitions(-D__LITTLE_ENDIAN__)
  
# 包含头文件目录  
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/eprosimartps
)  
  
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

# 添加一个动态库  
add_executable(
    test_Discovery 
    ${CMAKE_CURRENT_SOURCE_DIR}/test_Discovery.cpp
)  
  

find_package(Boost REQUIRED COMPONENTS filesystem system thread)
target_link_libraries(
    test_Discovery 
    fastrtps boost_system boost_filesystem boost_thread
)

# 如果需要，可以设置库的输出目录（可选）  
set_target_properties(
    test_Discovery  
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/lib
)