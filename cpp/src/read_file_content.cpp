
#include "read_file_content.h"
/**
 * Tries to read the content of a file into a std::string
 *
 * \param fileName to be read
 * \return if possible content of the file,
 *         else description what went wrong
 **/
Expected<std::string, std::string>
readFileContent(std::string const& fileName) {
    std::ifstream f(fileName);
    if (!f.is_open()) {
        return Unexpected("error while opening file " + fileName);
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    if (f.bad()) {
        return Unexpected("error while reading file " + fileName);
    }

    return buffer.str();
}
