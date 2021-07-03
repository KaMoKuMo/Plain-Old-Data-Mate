#pragma once

#include "expected.h"
#include "input_parameter.h"

ExpectedOrMessage<InputParameter>
convertCommandLineArguments(int argc, char const* argv[]);
