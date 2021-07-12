#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include <string>
#include <vector>

struct FilePositionRange {
    size_t start;
    size_t end;
};

struct NamespaceData {
    std::string name;
    FilePositionRange range;
};


/** @} */
