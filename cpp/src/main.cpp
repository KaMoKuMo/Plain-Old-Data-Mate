/**
 * @file main.cpp
 * Entry point of the tool
 */

#include "convert_command_line_arguments.h"
#include "parse_cpp_file.h"
#include <iostream>

int main(int argc, char const* argv[]) {
    auto result = convertCommandLineArguments(argc, argv);
    if (!result) {
        std::cout << result.error() << '\n';
        return 1;
    }
    auto const secondResult = parseCppFile(result->inputFileName);
    if (!secondResult) {
        std::cout << secondResult.error() << '\n';
        return 2;
    }
    return 0;
}
