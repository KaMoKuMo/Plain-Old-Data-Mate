#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"

#include <string>

Expected<std::pair<std::string::const_iterator, std::string::const_iterator>, std::string>
findInnerScope(std::string const& input, size_t offset);

/** *@}*/
