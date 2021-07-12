#pragma once

/** \addtogroup source_code_generation
 * @{
 */
#include "expected.h"
#include "file_parsing/struct_snippets.h"
#include "source_code_generation/details/source_code.h"

#include <memory>

struct GeneratedSources {
    std::unique_ptr<SourceCode> headerCode;
    std::unique_ptr<SourceCode> sourceCode;
};

GeneratedSources
generateSourceCode(std::vector<StructSnippets>);

/** @} */

