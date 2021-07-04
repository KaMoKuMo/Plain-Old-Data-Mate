#include "source_code_generation/details/source_code.h"

#include <sstream>

std::string
SourceCode::asString() const {
    std::stringstream data;
    write(data, 0);
    return data.str();
}

std::ostream&
operator<<(std::ostream& o, SourceCode const& rhs) {
    return rhs.write(o, 0);
}
