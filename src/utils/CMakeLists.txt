# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
file( GLOB SRCS *.c *.cpp *.cc *.h *.hpp )
aux_source_directory(. DIR_LIB_SRCS)
link_libraries(pthread)
# 生成链接库
add_library (utils ${DIR_LIB_SRCS})
