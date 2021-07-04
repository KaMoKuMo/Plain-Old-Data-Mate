
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
        auto const input = "struct foo{ };\n struct bah {int i;};\n";
        WHEN("partitionIntoStructStrings is called") {
            auto const result = partitionIntoStructStrings(input);
            THEN("two structs could be retrived") {
                REQUIRE(result->size() == 2);
            }
        }
    }
}


