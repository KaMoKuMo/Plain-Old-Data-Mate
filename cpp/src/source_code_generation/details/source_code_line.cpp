#include "source_code_generation/details/source_code_line.h"


SourceCodeLine::SourceCodeLine(std::string initalData)
    : _line(initalData)
{
}

SourceCodeLine&
SourceCodeLine::append(std::string additionalData) {
    _line.append(additionalData);
    return *this;
}

std::ostream&
SourceCodeLine::write(std::ostream& o, size_t indentationLevel) const {
    return LineFragment(_line).write(o, indentationLevel) << '\n';
}

SourceCodeLine
SourceCodeLine::operator+(std::string additionalData) const {
    auto copy = *this;
    copy.append(additionalData);
    return copy;
}
