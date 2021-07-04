
#the source code is packaged as a library to enable unit-tests
add_library(
    podmateLib
    src/convert_command_line_arguments.cpp
    src/input_parameter.cpp
    src/output_file_parameters.cpp

    #the parsing module
    src/file_parsing/parse_cpp_file.cpp
    src/file_parsing/details/collect_statements.cpp
    src/file_parsing/details/collect_structs.cpp
    src/file_parsing/details/extract_member_name.cpp
    src/file_parsing/details/extract_struct_snippets.cpp
    src/file_parsing/details/partition_into_struct_strings.cpp
    src/file_parsing/details/read_file_content.cpp
    src/file_parsing/details/find_inner_scope.cpp

    #source code generation module

    src/source_code_generation/write_source_files.cpp
    src/source_code_generation/function.cpp
    src/source_code_generation/line_fragment.cpp
    src/source_code_generation/variable_declaration.cpp
    src/source_code_generation/line_statement.cpp
    src/source_code_generation/source_code_line.cpp
    src/source_code_generation/write_equal_operator.cpp
    src/source_code_generation/source_code.cpp
    src/source_code_generation/body.cpp
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
