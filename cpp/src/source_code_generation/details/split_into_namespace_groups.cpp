#include "source_code_generation/details/split_into_namespace_groups.h"

#include <algorithm>

std::vector<std::vector<StructSnippets>>
splitIntoNamespaceGroups(std::vector<StructSnippets> const& snippets) {
    std::vector<std::vector<StructSnippets>> result;
    for (auto structSnippet : snippets) {
        auto it = std::find_if(
                result.begin(), result.end(),
                [&](auto const& namespaceGroupSnippets) {
                    //No empty vectors are created
                    //and all elements have equal namespaces
                   return namespaceGroupSnippets.front().namespaces == structSnippet.namespaces;
                });
        if (it != result.end()) {
            it->push_back(structSnippet);
        } else {
            result.push_back({structSnippet});
        }
    }

    return result;
}
