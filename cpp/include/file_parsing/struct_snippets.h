#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include <string>
#include <vector>


/**
 * Collection of names containing the struct name and the member names.
 * Result data returned from the file_parsing main function \see
 * parse_cpp_file()
 **/
struct StructSnippets {
    std::string name; //<! name of the struct
    std::vector<std::string> memberNames; //<! found member names
};

/** @} */
