#! /bin/sh

if [ $1 == 'clean' ];then
    rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile test.out utils.out polygon-net
elif [ $1 == 'build' ];then
    cmake .
    make
else
    echo 'Unknown ag'
fi
