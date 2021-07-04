#pragma once

#include "expected.h"
#include "struct_snippets.h"
#include "struct_name_with_content.h"

Expected<StructSnippets, std::string>
extractStructSnippets(StructNameWithContent const&);
