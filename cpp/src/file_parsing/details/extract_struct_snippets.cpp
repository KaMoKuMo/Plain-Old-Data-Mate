#include "file_parsing/details/extract_struct_snippets.h"

#include "file_parsing/details/calculate_surrounding_namespaces.h"
#include "file_parsing/details/collect_statements.h"
#include "file_parsing/details/extract_member_name.h"


/**
 * Partitions the content of a struct (in form of a string)
 * into member strings.
 * E.g. {"nameOfTheStruct", "int i;\n double d;"} -> {"nameOfTheStruct", ["i", "d"]}
 * 
 * The vector of NamespaceData might be shuffeld
 **/
Expected<StructSnippets, std::string>
extractStructSnippets(StructsRawData const& nameWithContent,
                      std::vector<NamespaceData>& namespaces) {
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

    auto surroundingNamespaces = calculateSurroundingNamespaces(
            nameWithContent.offset,
            namespaces
        );

    return StructSnippets {
        nameWithContent.name,
        memberNames,
        surroundingNamespaces
    };
}
