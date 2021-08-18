#include "source_code_generation/write_source_files.h"
#include "source_code_generation/details/function.h"
#include "source_code_generation/details/generate_source_code.h"


#include <fstream>

/**
 * writes the actual source files.
 * \param parameter contains the meta-data package for the source files to be generated
 * \return void, if everything worked,
 *         else description of the error
 **/
Expected<void, std::string>
writeSourceFiles(OutputParameter const& parameter) {

    //0. Check Requirements: the files to be generated can be opened and written to
    auto const fileFlags = std::ios_base::out | std::ios_base::trunc;
    auto sourceFileStream = std::fstream(parameter.outputFileData.sourceFileName, fileFlags);
    auto headerFileStream = std::fstream(parameter.outputFileData.headerFileName, fileFlags);

    if (sourceFileStream.fail()) {
        if (sourceFileStream.bad()) {
            return Unexpected(std::string("while writting source file, badbit has been set"));
        } else {
            return Unexpected(std::string("while writting source file, failbit has been set"));
        }
    }
    if (headerFileStream.fail()) {
        if (sourceFileStream.bad()) {
            return Unexpected(std::string("while writting header file, badbit has been set"));
        } else {
            return Unexpected(std::string("while writting header file, failbit has been set"));
        }
    }

    //1. Translate the struct informations into actual Function objects to write the files
    auto result = generateSourceCode(parameter.structSnippets);
    if (!result)
        return Unexpected(std::move(result).error());

    auto [headerFileCode, sourceFileCode] = *std::move(result);
    if (!headerFileCode)
        return Unexpected(std::string("header source code couldn't be generated"));
    if (!sourceFileCode)
        return Unexpected(std::string("cpp source code couldn't be generated"));

    //2. actual writing of the header file
    headerFileStream << "#pragma once\n";
    headerFileStream << "#include <iostream>\n";
    headerFileStream << "#include \"simdjson.h\"\n";
    headerFileStream << parameter.outputFileData.headerPreamble << '\n';
    headerFileStream << *headerFileCode;

    //3. actual writing of the source file
    sourceFileStream << parameter.outputFileData.sourcePreamble << '\n';
    sourceFileStream << *sourceFileCode;

    return {};
}
