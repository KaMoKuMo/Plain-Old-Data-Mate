#pragma once

#include "expected.h"
#include "struct_name_with_content.h"

#include <vector>

Expected<std::vector<StructNameWithContent>, std::string>
partitionIntoStructStrings(std::string const& cppFileContent);

