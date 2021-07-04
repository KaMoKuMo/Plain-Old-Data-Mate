#pragma once

#include "expected.h"
#include "struct_snippets.h"

Expected<std::vector<StructSnippets>, std::string>
parseCppFile(std::string const&);
