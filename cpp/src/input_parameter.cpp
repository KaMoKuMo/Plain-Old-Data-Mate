#include "input_parameter.h"

#include <tuple>

//! Compares every member of \see InputParameter
bool
operator==(InputParameter const& lhs, InputParameter const& rhs) {
    return lhs.inputFileName == rhs.inputFileName && lhs.outputData == rhs.outputData;
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
             << "\", \"output-parameter\" : \"" << parameter.outputData
             << "\"}";
}
