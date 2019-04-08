# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
file( GLOB SRCS *.c *.cpp *.cc *.h *.hpp )
# 项目信息
project (polygon-net)
# 查找当前目录下的所有源文件
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-g -O0)
    message(STATUS "Add compile options -g -o0")   
endif(CMAKE_COMPILER_IS_GNUCXX)
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(../ DIR_SRCS)
# 添加子目录
add_subdirectory(../utils utils.out)
add_subdirectory(../test test.out)
# 指定生成目标 
add_executable(polygon-net ${DIR_SRCS})
# 添加链接库
link_libraries(pthread)
target_link_libraries(polygon-net utils test)
