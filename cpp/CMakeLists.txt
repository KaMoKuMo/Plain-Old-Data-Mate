
#the source code is packaged as a library to enable unit-tests
add_library(
    podmateLib
    src/collect_statements.cpp
    src/collect_structs.cpp
    src/convert_command_line_arguments.cpp
    src/extract_member_name.cpp
    src/extract_struct_snippets.cpp
    src/input_parameter.cpp
    src/parse_cpp_file.cpp
    src/partition_into_struct_strings.cpp
    src/read_file_content.cpp
    src/find_inner_scope.cpp
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
