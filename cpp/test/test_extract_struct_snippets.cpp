#include <catch2/catch.hpp>

#include "file_parsing/details/extract_struct_snippets.h"

TEST_CASE("extractStructSnippets - most simple input", "[file_parsing]") {
    GIVEN("A struct definition with two members and a name") {
        auto const input = StructNameWithContent{"arbitraryName" , "int first;\n double second;\n"};
        WHEN("extractStructSnippets is called") {
            auto const result = extractStructSnippets(input);
            THEN("two member names are returned") {
                REQUIRE(result->memberNames.size() == 2);
            }
            THEN("the first member name matches") {
                REQUIRE(result->memberNames.front() == "first");
            }
            THEN("the second member name matches") {
                REQUIRE(result->memberNames.back() == "second");
            }
            THEN("the name of the struct matches") {
                REQUIRE(result->name == "arbitraryName");
            }
        }
    }
}
TEST_CASE("extractStructSnippets - edge cases", "[file_parsing]") {
    GIVEN("A struct definition with two inline documented members") {
        auto const input = StructNameWithContent{"", "int first; //!< firstMember\n double second; //<! secondMember\n"};
        WHEN("extractStructSnippets is called") {
            auto const result = extractStructSnippets(input);
            THEN("Neither member name contains any comment") {
                REQUIRE(result->memberNames.front() == "first");
                REQUIRE(result->memberNames.back() == "second");
                REQUIRE(result->memberNames.size() == 2);
            }
        }
    }
    GIVEN("A struct definition with two members and above documentation") {
        auto const input = StructNameWithContent{"", "//! firstMember\n int first;\n //! secondMember\n double second;\n"};
        WHEN("extractStructSnippets is called") {
            auto const result = extractStructSnippets(input);
            THEN("The documentation is ignored") {
                REQUIRE(result->memberNames.size() == 2);
                REQUIRE(result->memberNames.front() == "first");
                REQUIRE(result->memberNames.back() == "second");
            }
        }
    }
    GIVEN("A struct definition with arbitrary whitespaces") {
        auto const input = StructNameWithContent{"", " int \t\t first \v;  \n    double \n second \n\n;"};
        WHEN("extractStructSnippets is called") {
            auto const result = extractStructSnippets(input);
            THEN("the whitespaces are trimmed away") {
                REQUIRE(result->memberNames.size() == 2);
                REQUIRE(result->memberNames.front() == "first");
                REQUIRE(result->memberNames.back() == "second");
            }
        }
    }
}
