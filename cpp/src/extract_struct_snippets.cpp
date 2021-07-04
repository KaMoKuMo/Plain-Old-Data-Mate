#include "extract_struct_snippets.h"

#include "collect_statements.h"
#include "extract_member_name.h"


/**
 * Partitions the content of a struct (in form of a string)
 * into member strings.
 * E.g. {"nameOfTheStruct", "int i;\n double d;"} -> {"nameOfTheStruct", ["i", "d"]}
 **/
Expected<StructSnippets, std::string>
extractStructSnippets(StructNameWithContent const& nameWithContent) {
    auto statements = collectStatements(nameWithContent.content);

    std::vector<std::string> memberNames;
    memberNames.reserve(statements.size());
    for (auto const& statement : statements) {
        if (auto expectedMemberName = extractMemberName(statement)) {
            memberNames.emplace_back(*(std::move(expectedMemberName)));
        } else {
            return Unexpected(std::move(expectedMemberName).error());
        }
    }

    return StructSnippets {
        nameWithContent.name,
        memberNames
    };
}
