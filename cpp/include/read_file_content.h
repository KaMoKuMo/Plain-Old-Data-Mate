#pragma once

#include "expected.h"

Expected<std::string, std::string>
readFileContent(std::string const&);
