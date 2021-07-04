#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include "whitespaces.h"
#include <string>


//! trims of every whitespace in the beginning of the string
inline std::string
ltrim(std::string const& str) {
    size_t const startPos = str.find_first_not_of(whitespaces);
    return startPos == std::string::npos ? "" : str.substr(startPos);
}

//! trims of every whitespace at the end of the string
inline std::string
rtrim(std::string const& str) {
    size_t const endPos = str.find_last_not_of(whitespaces);
    return endPos == std::string::npos ? "" : str.substr(0, endPos + 1);
}

//! trims of whitespaces in the beginning and the end of the string
inline std::string
trim(std::string const& str) {
    return ltrim(rtrim(str));
}

/** *@}*/
