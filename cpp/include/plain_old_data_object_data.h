#pragma once

#include <string>
#include <vector>


/**
 * Neccessary Information to write comparison operators for data objects.
 **/
struct PlainOldDataObjectData {
    std::string objectName;
    std::vector<std::string> namespaces;
    std::vector<std::string> memberNames;
};
