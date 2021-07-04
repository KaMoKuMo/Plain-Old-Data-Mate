#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "file_parsing/struct_snippets.h"
#include "expected.h"

#include <vector>

Expected<std::vector<StructSnippets>, std::string>
collectStructs(std::string const& cppFileContent);

/** @} */
