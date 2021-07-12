#include <catch2/catch.hpp>

#include "file_parsing/details/collect_structs.h"

TEST_CASE("collectStructs - Happy Path", "[file_parsing]") {
    GIVEN("a one member struct within a namespace") {
        auto const input = "namespace Namespace { struct Data { int i; }; }";
        WHEN("collectStructs is called") {
            auto const result = collectStructs(input);
            THEN("one struct is retrived") {
                REQUIRE(result->size() == 1);
            }
            THEN("the struct name is deduced") {
                REQUIRE(result->front().name == "Data");
            }
            THEN("the struct has one member") {
                REQUIRE(result->front().memberNames.size() == 1);
            }
            THEN("the one member name is retrived") {
                REQUIRE(result->front().memberNames.front() == "i");
            }
            THEN("the struct is embedded within one namespace") {
                REQUIRE(result->front().namespaces.size() == 1);
            }
            THEN("the namespace name is retrived") {
                REQUIRE(result->front().namespaces.front() == "Namespace");
            }
        }
    }
}
