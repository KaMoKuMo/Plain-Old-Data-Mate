#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "expected.h"
#include "structs_raw_data.h"

#include <vector>

Expected<std::vector<StructsRawData>, std::string>
partitionIntoStructStrings(std::string const& cppFileContent);


/** *@}*/
