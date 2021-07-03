#include "input_parameter.h"

#include <tuple>

//! Helpermethod for the comparison operators 
auto tieData(InputParameter const& parameter) {
    return std::tie(parameter.inputFileName,
                    parameter.outputHeaderFileName,
                    parameter.outputSourceFileName);
}

//! Compares every member of \see InputParameter
bool
operator==(InputParameter const& lhs, InputParameter const& rhs) {
    return tieData(lhs) == tieData(rhs);
}

//! Compares every member of \see InputParameter
bool
operator!=(InputParameter const& lhs, InputParameter const& rhs) {
    return !(lhs == rhs);
}

//! streams the object in json format
std::ostream&
operator<<(std::ostream& o, InputParameter const& parameter) {
    return o << "{"
             << "\"input-file-name\" : \"" << parameter.inputFileName
             << "\", \"output-header-file-name\" : \"" << parameter.outputHeaderFileName
             << "\", \"output-source-file-name\" : \"" << parameter.outputSourceFileName
             << "\"}";
}
