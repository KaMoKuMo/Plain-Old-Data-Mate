#pragma once

#include <string>

#include <iostream>

#include "file_parsing/struct_snippets.h"
#include "output_file_parameters.h"

/**
 * Input for the last stage in the podmate app, the source code generation
 * @see writeSourceFiles()
 **/
struct OutputParameter {
    std::vector<StructSnippets> structSnippets; //<! translated struct data
    OutputFileParameters outputFileData; //<! data for the outputfiles
};

