#include "source_code_generation/details/write_left_shift_operator.h"
#include "source_code_generation/details/function.h"
#include "source_code_generation/details/source_code_collection.h"
#include "source_code_generation/details/source_code_line.h"

/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the equal operator.
 **/
Function
writeLeftShiftOperator(StructSnippets const& structData) {
    std::string variableName = "instance";
    auto writeMemberStream = [&](MemberSnippet const& member, bool isFirstLine) {
        auto line = std::make_unique<SourceCodeLine>();
        line->append("<< \"");
        if (!isFirstLine)
            line->append(", \\\"");
        else
            line->append(" \\\"");

        line->append(member.name);

        if (member.type == "std::string") {
            line->append("\\\" : \\\"\" << ");
        }
        else {
            line->append("\\\" : \" << ");
        }
        line->append(variableName + '.' + member.name);
        if (member.type == "std::string") {
            line->append(" << \"\\\"\"");
        }

        return line;
    };


    auto firstLine = std::make_unique<SourceCodeLine>();
    std::string streamName = "o";
    firstLine->append("return " + streamName + " << \'{\'");

    auto body = std::make_unique<SourceCodeCollection>();
    body->add(std::move(firstLine));
    bool isFirstLine = true;

    for (auto const& member : structData.member) {
        body->add(writeMemberStream(member, isFirstLine));
        isFirstLine = false;
    }

    body->add(std::make_unique<SourceCodeLine>("<< \" }\";"));

    return Function(
            "std::ostream&",
            "operator<<",
            {
                VariableDeclaration("std::ostream&", streamName),
                VariableDeclaration(structData.name + " const&", variableName)
            },
            std::move(body)
        );
}

