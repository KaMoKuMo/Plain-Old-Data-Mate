#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "file_parsing/details/namespace_data.h"

#include <vector>

std::vector<std::string>
calculateSurroundingNamespaces(size_t, std::vector<NamespaceData>&);

/** *@}*/

