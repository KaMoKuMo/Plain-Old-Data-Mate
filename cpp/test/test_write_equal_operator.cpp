#include <catch2/catch.hpp>

#include "source_code_generation/details/write_equal_operator.h"
#include "file_parsing/struct_snippets.h"

TEST_CASE("writeEqualOperator - single member struct", "[SourceCodeGeneration]") {
    GIVEN("A Struct Snippet of a struct with a single member") {
        auto const input = StructSnippets{"foo", {"member"}};
        WHEN("writeEqualOperator is called") {
            auto result = writeEqualOperator(input);
            THEN("the function definition matches") {
                std::string const expectedDefinition = "bool operator==(foo const& lhs, foo const& rhs) {\n"
                                                       "    return lhs.member == rhs.member;\n"
                                                       "}\n";
                REQUIRE(expectedDefinition == result.asString());
            }
            THEN("the function declartion matches") {
                std::string const expectedDeclaration = "bool operator==(foo const& lhs, foo const& rhs);\n";
                REQUIRE(expectedDeclaration == result.asDeclaration().asString());
            }
        }
    }
}

