/**
 * @file main.cpp
 * Entry point of the tool
 */

#include "convert_command_line_arguments.h"
#include <iostream>

int main(int argc, char const* argv[]) {
    auto result = convertCommandLineArguments(argc, argv);
    if (!result) {
        std::cout << result.error() <<'\n';
        return -1;
    }
    return 0;
}
