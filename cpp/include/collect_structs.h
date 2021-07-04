#pragma once

#include "struct_snippets.h"
#include "expected.h"

#include <vector>

Expected<std::vector<StructSnippets>, std::string>
collectStructs(std::string const& cppFileContent);

