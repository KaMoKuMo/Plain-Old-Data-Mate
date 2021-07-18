#pragma once

/** \addtogroup file_parsing
 * @{
 */

#include <string>
#include <vector>


/**
 * separated data for a member of a struct
 **/
struct MemberSnippet {
    std::string type;
    std::string name;
};

/**
 * Collection of names containing the struct name and the member names.
 * Result data returned from the file_parsing main function \see
 * parse_cpp_file()
 **/
struct StructSnippets {
    std::string name; //<! name of the struct
    std::vector<MemberSnippet> member; //<! found member names
    std::vector<std::string> namespaces; //<! surrounding namespaces. The first one being the outtermost namespace
};

/** @} */
