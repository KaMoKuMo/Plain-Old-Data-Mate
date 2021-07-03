
#include <catch2/catch.hpp>

#include "convert_command_line_arguments.h"

TEST_CASE("ConvertCommandLineArguments", "[unittest]") {
    GIVEN("three input arguments") {
        int const argc = 4;
        char const* argv[] = {"Programmaufruf", "input", "header", "source"};
        WHEN("convertCommandLineArguments is called") {
            auto const result = convertCommandLineArguments(argc, argv);
            THEN("a set of InputParameter is returned") {
                REQUIRE(InputParameter{"input", "header", "source"} == result);
            }
        }
    }
    GIVEN("one input argument is missing") {
        int const argc = 3;
        char const* argv[] = {"Programmaufruf", "input", "source"};
        WHEN("convertCommandLineArguments is called") {
            auto const result = convertCommandLineArguments(argc, argv);
            THEN("No InputParameter are returned") {
                REQUIRE(!static_cast<bool>(result));
            }
        }
    }
}

