#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"
#include "file_parsing/struct_snippets.h"
#include "file_parsing/details/struct_name_with_content.h"

Expected<StructSnippets, std::string>
extractStructSnippets(StructNameWithContent const&);

/** *@}*/
