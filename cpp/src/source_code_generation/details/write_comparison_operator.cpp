#include "source_code_generation/details/write_comparison_operator.h"

#include "source_code_generation/details/variable_declaration.h"
#include "source_code_generation/details/line_statement.h"


/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the given comparison and accumulation operator.
 **/
Function
writeComparisonOperator(StructSnippets const& structData,
                        std::string const& comparison,
                        std::string const& aggregateOperator,
                        std::string const& defaultValue) {
    std::vector<std::string> memberComparisions;
    std::string const lhs("lhs");
    std::string const rhs("rhs");
    memberComparisions.reserve(structData.member.size());
    for (auto const& member : structData.member) {
        memberComparisions.emplace_back(lhs + '.' + member.name + " " + comparison + " "  + rhs + '.' + member.name);
    }
    std::string aggregatedComparison("return ");

    auto itB = memberComparisions.begin();
    auto const itE = memberComparisions.end();
    if (itB != itE) {
        aggregatedComparison += *itB;
        ++itB;
        for (; itB != itE ; ++itB) {
            aggregatedComparison += " " + aggregateOperator + " " + *itB;
        }
    } else {
        aggregatedComparison += defaultValue;
    }

    return Function("bool",
                    "operator" + comparison,
                    {
                        VariableDeclaration(structData.name + " const&", lhs),
                        VariableDeclaration(structData.name + " const&", rhs)
                    },
                    std::make_unique<LineStatement>(aggregatedComparison)
            );
}

