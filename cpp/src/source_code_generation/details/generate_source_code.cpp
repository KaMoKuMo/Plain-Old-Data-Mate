#include "source_code_generation/details/generate_source_code.h"

#include "source_code_generation/details/namespace.h"
#include "source_code_generation/details/source_code_collection.h"
#include "source_code_generation/details/split_into_namespace_groups.h"
#include "source_code_generation/details/write_from_json.h"
#include "source_code_generation/details/write_left_shift_operator.h"
#include "source_code_generation/details/write_equal_operator.h"
#include "source_code_generation/details/write_unequal_operator.h"

#include <numeric>

Expected<GeneratedSources, std::string>
generateSourceCode(std::vector<StructSnippets> snippets) {
    auto namespaceGroupedSnippets = splitIntoNamespaceGroups(snippets);

    auto embedIntoNamespaces = [](std::vector<std::string> const& namespaces, std::unique_ptr<SourceCode> code) {
        return std::accumulate(
            namespaces.rbegin(), namespaces.rend(),
            std::move(code),
            [](auto&& sourceCode, std::string namespaceName) -> std::unique_ptr<SourceCode>{
                return std::make_unique<Namespace>(namespaceName, std::move(sourceCode));
            }
        );

    };

    auto header = std::make_unique<SourceCodeCollection>();
    auto source = std::make_unique<SourceCodeCollection>();
    for (auto const& groupedSnippets : namespaceGroupedSnippets) {
        if (groupedSnippets.empty())
            continue;
        std::vector<Function> functions;
        for (auto const& structSnippets : groupedSnippets) {
            functions.emplace_back(writeEqualOperator(structSnippets));
            functions.emplace_back(writeUnequalOperator(structSnippets));
            functions.emplace_back(writeLeftShiftOperator(structSnippets));
            auto result = writeFromJson(structSnippets);
            if (result) {
                functions.emplace_back(*std::move(result));
            } else {
                return Unexpected(std::move(result).error());
            }
        }

        auto headerCollection = std::make_unique<SourceCodeCollection>();
        auto sourceCollection = std::make_unique<SourceCodeCollection>();
        for (auto&& function : functions) {
            headerCollection->add(std::make_unique<Function>(function.asDeclaration()));
            sourceCollection->add(std::make_unique<Function>(std::move(function)));
        }

        header->add(embedIntoNamespaces(groupedSnippets.front().namespaces, std::move(headerCollection)));
        source->add(embedIntoNamespaces(groupedSnippets.front().namespaces, std::move(sourceCollection)));
    }
    return GeneratedSources{std::move(header), std::move(source)};
}
