#!/bin/bash

BUILD=Debug

#run cmake in build directory
mkdir -p $BUILD
CXX=clang++ CC=clang cmake -B $BUILD -S ./ -D ENABLE_COVERAGE:BOOL=TRUE -DCMAKE_BUILD_TYPE=$BUILD || exit $?

#actual build
cmake --build $BUILD -j6 || exit $?

#and test
cd $BUILD
LLVM_PROFILE_FILE="unittests.profraw" ./bin/unittests
llvm-profdata-10 merge -sparse unittests.profraw -o unittests.profdata
llvm-cov-10 show ./bin/unittests -instr-profile=unittests.profdata
llvm-cov-10 report ./bin/unittests -instr-profile=unittests.profdata
