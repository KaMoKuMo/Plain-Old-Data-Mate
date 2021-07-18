cmake_minimum_required(VERSION 3.15)

project(SampleProject)

add_executable(cli
               cli.cpp
               sample_structs_operators.cpp)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(
  NAME
  bincrafters
  URL
  https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
  REQUIRES
  ${CONAN_EXTRA_REQUIRES}
  simdjson/0.9.5
  OPTIONS
  ${CONAN_EXTRA_OPTIONS}
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD
  missing)


target_compile_features(cli PUBLIC cxx_std_17)

target_link_libraries(cli PRIVATE CONAN_PKG::simdjson)
