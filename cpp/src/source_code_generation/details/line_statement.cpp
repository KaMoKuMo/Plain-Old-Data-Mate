#include "source_code_generation/details/line_statement.h"


LineStatement::LineStatement(std::string initialData)
    : _lineStatment(initialData)
{
}

LineStatement&
LineStatement::append(std::string additionalData) {
    _lineStatment.append(additionalData);
    return *this;
}

std::ostream&
LineStatement::write(std::ostream& o, size_t indentationLevel) const {
    return (_lineStatment + ";").write(o, indentationLevel);
}
