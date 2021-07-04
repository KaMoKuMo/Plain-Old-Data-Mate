#include "source_code_generation/variable_declaration.h"
#include "source_code_generation/line_fragment.h"

VariableDeclaration::VariableDeclaration(std::string type, std::string name)
    : _type(type)
    , _name(name) 
{
}

std::ostream&
VariableDeclaration::write(std::ostream& o, size_t indentationLevel) const {
    return LineFragment(_type + " " + _name).write(o, indentationLevel);
}
