# CMake 最低版本要求，这里指定最低要求为3.10版本，可根据实际情况调整
cmake_minimum_required(VERSION 3.10)

# 项目名称，可自行修改，这里设为my_project
project(my_project)

# 添加可执行文件，这里添加webbench.c文件
add_executable(webbench webbench.c)