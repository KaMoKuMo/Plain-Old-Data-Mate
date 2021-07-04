
#include "file_parsing/details/extract_member_name.h"
#include "file_parsing/details/trim.h"
#include "file_parsing/details/whitespaces.h"

/**
 * extracts the name of a member from a given member definition (missing the semicolon).
 * E.g. "int importantNumber " -> "importantNumber"
 *
 * \param memberDefinition contains a member definition without the finializing semicolon
 * \return the found name, or a description that no name could be found
 **/
Expected<std::string, std::string>
extractMemberName(std::string const& memberDefinition) {
    auto const memberstring = trim(memberDefinition);

    size_t const lastWhitespaceIndex = memberstring.find_last_of(whitespaces);
    if (lastWhitespaceIndex == std::string::npos) {
        return Unexpected(std::string("Kein Name gefunden"));
    }

    return trim(memberstring.substr(lastWhitespaceIndex + 1));
}
