#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"
#include "file_parsing/struct_snippets.h"
#include "file_parsing/details/namespace_data.h"
#include "file_parsing/details/structs_raw_data.h"

Expected<StructSnippets, std::string>
extractStructSnippets(StructsRawData const&, std::vector<NamespaceData>&);

/** *@}*/
