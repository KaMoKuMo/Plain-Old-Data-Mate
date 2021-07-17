
#the source code is packaged as a library to enable unit-tests
add_library(
    podmateLib STATIC
    src/convert_command_line_arguments.cpp
    src/input_parameter.cpp
    src/output_file_parameters.cpp

    #the parsing module
    src/file_parsing/parse_cpp_file.cpp
    src/file_parsing/details/calculate_surrounding_namespaces.cpp
    src/file_parsing/details/collect_namespaces.cpp
    src/file_parsing/details/collect_statements.cpp
    src/file_parsing/details/collect_structs.cpp
    src/file_parsing/details/extract_member_name.cpp
    src/file_parsing/details/extract_struct_snippets.cpp
    src/file_parsing/details/find_inner_scope.cpp
    src/file_parsing/details/partition_into_struct_strings.cpp
    src/file_parsing/details/read_file_content.cpp

    #source code generation module
    src/source_code_generation/write_source_files.cpp
    src/source_code_generation/details/body.cpp
    src/source_code_generation/details/function.cpp
    src/source_code_generation/details/generate_source_code.cpp
    src/source_code_generation/details/line_fragment.cpp
    src/source_code_generation/details/line_statement.cpp
    src/source_code_generation/details/namespace.cpp
    src/source_code_generation/details/source_code.cpp
    src/source_code_generation/details/source_code_collection.cpp
    src/source_code_generation/details/source_code_line.cpp
    src/source_code_generation/details/split_into_namespace_groups.cpp
    src/source_code_generation/details/variable_declaration.cpp
    src/source_code_generation/details/write_comparison_operator.cpp
    src/source_code_generation/details/write_equal_operator.cpp
    src/source_code_generation/details/write_left_shift_operator.cpp
    src/source_code_generation/details/write_unequal_operator.cpp
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
