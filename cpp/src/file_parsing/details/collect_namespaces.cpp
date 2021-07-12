#include "file_parsing/details/collect_namespaces.h"

#include "file_parsing/details/find_inner_scope.h"
#include "file_parsing/details/trim.h"

/**
 * Collects namespaces with their ranges within a cpp file.
 * If the content does not contain a namespace definition no error is emitted,
 * but an empty result range.
 * Notice that a namespace can appear multiple times in the result vector
 * (in case the cppFile contains multiple ranges for the namespace).
 * This should not be a problem for localizing a struct within namespaces,
 * as the scopes can't interleave.
 *
 * \param cppFileContent to be partitioned
 * \return collection of \see NamespaceData if processable,
 *         else a description of the problem
 **/
Expected<std::vector<NamespaceData>, std::string>
collectNamespaces(std::string const& cppFileContent) {
    std::vector<NamespaceData> result;
    size_t offset = 0;
    auto calculateOffset = [&](auto const iterator)
    {
        return static_cast<size_t>(iterator - cppFileContent.begin());
    };
    while (true){
        offset = cppFileContent.find("namespace", offset);
        if (offset == std::string::npos) {
            break;
        }
        auto expectedScope = findInnerScope(cppFileContent, offset);
        if (!expectedScope)
            return Unexpected(std::move(expectedScope).error());

        //Only if a scope can be found same members are returned
        if (expectedScope->first != expectedScope->second) {
            result.emplace_back(
                NamespaceData{
                    trim( std::string( cppFileContent.begin() + static_cast<long>(offset) + 9 /*length of namespace*/ , expectedScope->first - 1)), //-> name of the namespace
                    FilePositionRange{
                        calculateOffset(expectedScope->first - 1),
                        calculateOffset(expectedScope->second + 1)
                    }
                }
            );
        }
        offset = static_cast<size_t>(expectedScope->first - cppFileContent.begin());
    }
    return result;
}

