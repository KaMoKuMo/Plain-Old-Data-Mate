
BUILD=Debug

#run cmake in build directory
mkdir -p $BUILD
CXX=clang++ CC=clang cmake -B $BUILD -S ./ -DCMAKE_BUILD_TYPE=$BUILD || return $?

#actual build
cmake --build $BUILD -j6 || return $?

#and test
cd $BUILD
ctest --output-on-failure
