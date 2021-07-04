
#include "find_inner_scope.h"

/**
 * Given a string and an offset, the next content of the scope is marked.
 * E.g. Given "namespace Namespace{\n struct foo{\n int i;\n double d;};\n}",
 *  with an offset of 0 the function returns iterators marking the scope of
 *  Namespace.
 *  With an offset just befor the struct scope the function returns iterators
 *  marking the inner scope of the struct foo.
 *
 *  In case no scope is found an empty range at the end of the referenceContent
 *  is returned
 *
 * \param referenceContent which is searched
 * \param offset, where the search should start
 * \return range marking the scope within the referenceContent
 *
 **/
Expected<std::pair<std::string::const_iterator, std::string::const_iterator>, std::string>
findInnerScope(std::string const& referenceContent, size_t offset) {
    char const opening = '{';
    char const closing = '}';
    size_t const openingPos = referenceContent.find(opening, offset);
    if (openingPos == std::string::npos) {
        return {referenceContent.end(), referenceContent.end()};
    }
    unsigned int scopeCount = 1;
    auto const itB = std::next(referenceContent.begin(), static_cast<long>(openingPos + 1));
    auto itM = itB;
    auto const itE = referenceContent.end();
    while (itM != itE) {
        if (*itM == opening) {
            ++scopeCount;
        }
        else if (*itM == closing) {
            if (0 == --scopeCount)
                break;
        }
        ++itM;
    }
    if (scopeCount == 0) {
        return {itB, itM};
    }
    return Unexpected(std::string("no matching \"") + closing + "\" found");
}
