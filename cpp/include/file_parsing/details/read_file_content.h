#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"

Expected<std::string, std::string>
readFileContent(std::string const&);

/** *@}*/
