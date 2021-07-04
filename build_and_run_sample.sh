#!/bin/bash

#run the usual build script
./build.sh || return $?

#generate the source files
./Debug/bin/podmate ./sample/sample_structs.h ./sample/sample_structs_operators.h ./sample/sample_structs_operators.cpp "#include \"sample_structs.h\"" "#include \"sample_structs_operators.h\"" || return $?


#checking the generated source code; the success should become visible on the commandline
#and should yield a "0"

#little helper
function cleanup {
    rm sample_structs_operators.h sample_structs_operators.cpp
}

cd sample

#run the local build script i.d. execute cmake within the directory "Debug"
./build.sh || cleanup

#run the sample application which will generate some sample data and compare the instances
./Debug/cli

#run unconditionally the cleanup to ensure proper testing (the next time)
cleanup
rm -rf Debug
