#include "file_parsing/details/collect_structs.h"

#include "expected_invoke.h"
#include "file_parsing/details/collect_namespaces.h"
#include "file_parsing/details/extract_struct_snippets.h"
#include "file_parsing/details/partition_into_struct_strings.h"

/**
 * Reads the content of a cpp file and extracts the neccessary information
 * to generate source code for structs defined within the file.
 *
 * \param cppFileContent holds the data to be processed
 * \return if the structs are processable a collection of information,
 *         else a description of the encountered problem.
 **/
Expected<std::vector<StructSnippets>, std::string>
collectStructs(std::string const& cppFileContent) {
    auto mergeStructInformation = [](std::vector<StructsRawData> const& structData,
                                     std::vector<NamespaceData>& namespaceData) -> Expected<std::vector<StructSnippets>, std::string> {
        std::vector<StructSnippets> result;
        result.reserve(expectedStructs->size());
        for (auto const& structString : structData {
            if (auto expectedInformation = extractStructSnippets(structString, namespaceData)) {
                result.emplace_back(*(std::move(expectedInformation)));
            } else {
                return Unexpected(std::move(expectedInformation).error());
            }
        }
        return result;
    };

    return expected_invoke(mergeStructInformation,
                           partitionIntoStructStrings(cppFileContent),
                           collectNamespaces(cppFileContent));


}
