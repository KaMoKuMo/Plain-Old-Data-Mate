#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include <string>

/**
 * Rough cut of a struct string and its position within a file.
 **/
struct StructsRawData {
    std::string name; //!< the name of the struct
    std::string content; //!< the content within the scope of the struct definition

    /**
     * starting position of the struct within the file.
     * Not the absolute, but the relative Position regarding namespace ranges is important.
     **/
    size_t offset;
};

/** *@}*/
