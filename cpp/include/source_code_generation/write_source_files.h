#pragma once

/** \addtogroup source_code_generation
 * @{
 */
#include "expected.h"
#include "output_parameter.h"

Expected<void, std::string>
writeSourceFiles(OutputParameter const&);

/** @} */
