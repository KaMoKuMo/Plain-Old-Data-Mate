
#include <catch2/catch.hpp>

#include "file_parsing/details/partition_into_struct_strings.h"


TEST_CASE("partitionIntoStructStrings - with no structs", "[file_parsing]") {
    GIVEN("A content string without a struct") {
        auto const input = "arbitrary Content";
        WHEN("partitionIntoStructStrings is called") {
            auto const result = partitionIntoStructStrings(input);
            THEN("no failure happens") {
                REQUIRE(static_cast<bool>(result));
            }
            THEN("no information could be retrieved") {
                REQUIRE(result->size() == 0);
            }
        }
    }
}
TEST_CASE("partitionIntoStructStrings - with two structs", "[file_parsing]") {
    GIVEN("A content string with two structs") {
        std::string const input = "struct foo{ };\n struct bah {int i;};\n";
        WHEN("partitionIntoStructStrings is called") {
            auto const result = partitionIntoStructStrings(input);
            THEN("two structs could be retrived") {
                REQUIRE(result->size() == 2);
            }
            THEN("the offset of the first corresponds to the start position of the first \"struct\"") {
                size_t secondNameStartPosition = input.find("struct");
                REQUIRE(secondNameStartPosition != std::string::npos);
                REQUIRE(secondNameStartPosition == result->front().offset);
            }
            THEN("the offset of the second corresponds to the start position of the second \"struct\"") {
                size_t secondNameStartPosition = input.find("struct");
                secondNameStartPosition = input.find("struct", secondNameStartPosition + 1);
                REQUIRE(secondNameStartPosition != std::string::npos);
                REQUIRE(secondNameStartPosition == result->back().offset);
            }
        }
    }
}


