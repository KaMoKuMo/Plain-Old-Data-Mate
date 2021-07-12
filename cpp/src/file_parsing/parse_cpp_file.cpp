
#include "expected_invoke.h"
#include "file_parsing/parse_cpp_file.h"
#include "file_parsing/details/read_file_content.h"
#include "file_parsing/details/collect_structs.h"

/**
 * Main function of the file_parsing module.
 * Parses a file into the neccessary Information for the source code generation
 *
 * \param fileName to be parsed
 * \return if the file exists, can be read und the content is conformant, the neccessary Information is collected,
 *         else a description with the problem is yielded.
 **/
Expected<std::vector<StructSnippets>, std::string>
parseCppFile(std::string const& fileName) {
    return expected_invoke(collectStructs, readFileContent(fileName));
}
