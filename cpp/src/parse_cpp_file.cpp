
#include "parse_cpp_file.h"
#include "read_file_content.h"

/**
 * Parses a file into the neccessary Information for the source code generation
 *
 * \param fileName to be parsed
 * \return if the file exists, can be read und the content is cpp conformant, the neccessary Information is collected,
 *         else a description with the problem is yielded.
 **/
Expected<std::vector<PlainOldDataObjectData>, std::string>
parseCppFile(std::string const& fileName) {
    auto expectedContent = readFileContent(fileName);
    if (!expectedContent)
        return std::move(expectedContent).error();

    //auto expectedNamespaces = collectNamespaces(*expectedContent);
    //if (!expectedNamespaces)
    //  return std::move(expectedNamespaces).error();
    //
    //auto expectedStructs = collectStructs(*expectedContent);
    //if (!expectedStructs)
    //    return std::move(expectedStructs).error();
    //
    //return mergeInformation(*expectedNamespaces, *expectedStructs);
    //

    return std::vector<PlainOldDataObjectData>{};
}
