cmake_minimum_required(VERSION 3.15)

project(SampleProject)

add_executable(cli
               cli.cpp
               sample_structs_operators.cpp)


target_compile_features(cli PUBLIC cxx_std_17)
