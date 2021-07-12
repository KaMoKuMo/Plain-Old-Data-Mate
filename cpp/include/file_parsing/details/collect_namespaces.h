#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"
#include "namespace_data.h"

#include <vector>

Expected<std::vector<NamespaceData>, std::string>
collectNamespaces(std::string const& cppFileContent);


/** *@}*/

