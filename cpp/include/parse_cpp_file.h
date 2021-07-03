#pragma once

#include "expected.h"
#include "plain_old_data_object_data.h"

Expected<PlainOldDataObjectData, std::string>
parseCppFile(std::string const&);
