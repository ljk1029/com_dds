cmake_minimum_required(VERSION 3.10)  
project(MyProject)  
  
# 指定 C++ 标准  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  

add_definitions(-D__LITTLE_ENDIAN__)
  
# 包含头文件目录  
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/dds
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/writer
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/common
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/common/attributes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/qos
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/reader
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/timedevent
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/resources
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/discovery
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eprosimartps/discovery/data
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/submessages/
)  
  
# 查找源文件  
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/*.cpp")  
  
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/   SOURCE_API) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/dds           SOURCE_API_1) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/discovery     SOURCE_API_2) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/qos           SOURCE_API_3) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/reader        SOURCE_API_4) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/resources     SOURCE_API_5) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/submessages   SOURCE_API_6) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/timedevent   SOURCE_API_7) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/utils    SOURCE_API_8) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/writer   SOURCE_API_9) 



# 添加一个动态库  
add_library(
   fastrtps 
   SHARED 
   ${SRC_FILES}
)  



add_executable(
    test 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test3.cpp
    ${SOURCE_API}
    ${SOURCE_API_1}
    ${SOURCE_API_2}
    ${SOURCE_API_3}
    ${SOURCE_API_4}
    ${SOURCE_API_5}
    ${SOURCE_API_6}
    ${SOURCE_API_7}
    ${SOURCE_API_8}
    ${SOURCE_API_9}
)

#find_package(Boost REQUIRED COMPONENTS system filesystem)
#include_directories(${Boost_INCLUDE_DIRS})
#target_link_libraries(test ${Boost_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS filesystem system thread)
target_link_libraries(test boost_system boost_filesystem boost_thread)
  
# 如果需要，可以设置库的输出目录（可选）  
set_target_properties(
    #fastrtps
    test 
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/lib
)