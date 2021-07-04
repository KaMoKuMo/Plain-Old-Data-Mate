#pragma once

#include <string>
#include <vector>


/**
 * Collection of names containing the struct name and the member names
 **/
struct StructSnippets {
    std::string name; //<! name of the struct
    std::vector<std::string> memberNames; //<! found member names
};
