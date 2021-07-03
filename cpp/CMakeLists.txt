
#the source code is packaged as a library to enable unit-tests
add_library(
    podmateLib
    src/convert_command_line_arguments.cpp
    src/input_parameter.cpp
    src/parse_cpp_file.cpp
)

target_include_directories(
    podmateLib
    PUBLIC
        include
)

target_link_libraries(
    podmateLib
    PRIVATE
        project_options
        project_warnings
        CONAN_PKG::docopt.cpp
)

add_executable(
    podmate
    src/main.cpp
)

target_link_libraries(
    podmate
    PRIVATE
        project_options
        project_warnings
        podmateLib
)

if(ENABLE_TESTING)
   add_subdirectory(test)
endif()
