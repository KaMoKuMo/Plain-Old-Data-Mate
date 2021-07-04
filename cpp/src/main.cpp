/**
 * @file main.cpp
 * Entry point of the tool
 */

#include "convert_command_line_arguments.h"
#include "file_parsing/parse_cpp_file.h"
#include "source_code_generation/write_source_files.h"
#include <iostream>

int main(int argc, char const* argv[]) {
    auto parameter = convertCommandLineArguments(argc, argv);
    if (!parameter) {
        std::cout << parameter.error() << '\n';
        return 1;
    }
    auto const expectedStructInformation = parseCppFile(parameter->inputFileName);
    if (!expectedStructInformation) {
        std::cout << expectedStructInformation.error() << '\n';
        return 2;
    }

    auto const expectedWrittenFiles = writeSourceFiles(OutputParameter{*std::move(expectedStructInformation), parameter->outputData});
    if (!expectedWrittenFiles) {
        std::cout << expectedWrittenFiles.error() <<'\n';
        return 3;
    }

    return 0;
}
