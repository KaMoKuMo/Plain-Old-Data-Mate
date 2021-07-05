#include "source_code_generation/write_source_files.h"
#include "source_code_generation/details/function.h"
#include "source_code_generation/details/write_equal_operator.h"
#include "source_code_generation/details/write_unequal_operator.h"


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
    std::vector<Function> functionDefinitions;
    functionDefinitions.reserve(parameter.structSnippets.size() * 2);
    for (auto const& snippets : parameter.structSnippets) {
        functionDefinitions.emplace_back(writeEqualOperator(snippets));
        functionDefinitions.emplace_back(writeUnequalOperator(snippets));
    }

    //2. actual writing of the header file
    headerFileStream << "#pragma once\n";
    headerFileStream << parameter.outputFileData.headerPreamble << '\n';
    for (auto const& definition : functionDefinitions) {
        headerFileStream << definition.asDeclaration();
    }

    //3. actual writing of the source file
    sourceFileStream << parameter.outputFileData.sourcePreamble << '\n';
    for (auto const& definition : functionDefinitions) {
        sourceFileStream << definition;
    }

    return {};
}
