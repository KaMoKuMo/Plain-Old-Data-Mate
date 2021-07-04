#pragma once

#include "expected.h"
#include "input_parameter.h"

Expected<InputParameter, std::string>
convertCommandLineArguments(int argc, char const* argv[]);
