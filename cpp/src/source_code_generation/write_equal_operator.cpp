#include "source_code_generation/write_equal_operator.h"

#include "source_code_generation/variable_declaration.h"
#include "source_code_generation/line_statement.h"


/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the equal operator.
 **/
Function
writeEqualOperator(StructSnippets const& structData) {
    std::vector<std::string> memberComparisions;
    std::string const lhs("lhs");
    std::string const rhs("rhs");
    memberComparisions.reserve(structData.memberNames.size());
    for (auto const& memberName : structData.memberNames) {
        memberComparisions.emplace_back(lhs + '.' + memberName + " == " + rhs + '.' + memberName);
    }
    std::string aggregatedComparison("return ");

    auto itB = memberComparisions.begin();
    auto const itE = memberComparisions.end();
    if (itB != itE) {
        aggregatedComparison += *itB;
        ++itB;
        for (; itB != itE ; ++itB) {
            aggregatedComparison += " && " + *itB;
        }
    } else {
        aggregatedComparison += "true";
    }

    return Function("bool",
                    "operator==",
                    {
                        VariableDeclaration(structData.name + " const&", lhs),
                        VariableDeclaration(structData.name + " const&", rhs)
                    },
                    std::make_unique<LineStatement>(aggregatedComparison)
            );
}
