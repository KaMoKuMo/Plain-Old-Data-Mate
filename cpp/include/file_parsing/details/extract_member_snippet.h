#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"
#include "file_parsing/struct_snippets.h"

#include <string>

Expected<MemberSnippet, std::string>
extractMemberSnippet(std::string const& memberDefinition);

/** @}*/
