#!/bin/bash

BUILD=Debug

#run cmake in build directory
mkdir -p $BUILD
CXX=clang++ CC=clang cmake -B $BUILD -S ./ -DCMAKE_BUILD_TYPE=$BUILD || exit $?

#actual build
cmake --build $BUILD -j6 || exit $?

#and test
cd $BUILD
ctest --output-on-failure
