#include "output_file_parameters.h"

#include <iostream>
#include <tuple>

auto tieData(OutputFileParameters const& data) {
    return std::tie(
        data.headerFileName,
        data.sourceFileName,
        data.headerPreamble,
        data.sourcePreamble
    );
}

bool
operator==(OutputFileParameters const& lhs, OutputFileParameters const& rhs) {
    return tieData(lhs) == tieData(rhs);
}
bool
operator!=(OutputFileParameters const& lhs, OutputFileParameters const& rhs) {
    return !(lhs == rhs);
}

std::ostream&
operator<<(std::ostream& o, OutputFileParameters const& parameter) {
    return o << "{ \"headerFileName\" : \"" << parameter.headerFileName
             << "\", \"sourceFileName\" : \"" << parameter.sourceFileName
             << "\", \"headerPreamble\" : \"" << parameter.headerPreamble
             << "\", \"sourcePreamble\" : \"" << parameter.sourcePreamble
             << "\"}";

}
