
#include "file_parsing/details/extract_member_snippet.h"
#include "file_parsing/details/trim.h"
#include "file_parsing/details/whitespaces.h"

/**
 * extracts the name of a member from a given member definition (missing the semicolon).
 * E.g. "int importantNumber " -> {"int", "importantNumber"}
 *
 * \param memberDefinition contains a member definition without the finializing semicolon
 * \return the found name, or a description that no name could be found
 **/
Expected<MemberSnippet, std::string>
extractMemberSnippet(std::string const& memberDefinition) {
    auto const memberstring = trim(memberDefinition);

    size_t const lastWhitespaceIndex = memberstring.find_last_of(whitespaces);
    if (lastWhitespaceIndex == std::string::npos) {
        return Unexpected(std::string("Kein Name gefunden"));
    }
    //kann wegen trim nicht auf npos landen
    auto const lastNonWhitespaceIndex = memberstring.find_last_not_of(whitespaces, lastWhitespaceIndex);

    auto const type = trim(memberstring.substr(0, lastNonWhitespaceIndex + 1));
    auto const name = trim(memberstring.substr(lastWhitespaceIndex + 1));

    return MemberSnippet{type, name};
}
