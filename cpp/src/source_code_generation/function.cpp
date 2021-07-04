#include "source_code_generation/function.h"
#include "source_code_generation/line_fragment.h"
#include "source_code_generation/line_statement.h"

#include <sstream>

Function::Function(std::string returnType, std::string name,
                   std::vector<VariableDeclaration> arguments,
                   std::unique_ptr<SourceCode> body)
    : _returnType(returnType)
    , _name(name)
    , _arguments(arguments)
    , _body(body ? std::optional<Body>(std::move(body)) : std::nullopt)
{
}

std::ostream&
Function::write(std::ostream& o, size_t indentationLevel) const {
    LineFragment(_returnType + " " + _name).write(o, indentationLevel);

    //writing the argumentlist
    std::stringstream argumentList;
    argumentList << "(";
    auto itB = _arguments.begin();
    auto const itE = _arguments.end();
    if (itB != itE) {
        itB->write(argumentList, 0);
        ++itB;
    }
    for (; itB != itE; ++itB) {
        argumentList << ", ";
        itB->write(argumentList, 0);
    }
    argumentList << ")";
    std::string arguments = argumentList.str();

    if (_body) {
        LineFragment(arguments).write(o, 0);
        _body->write(o, indentationLevel);
        return LineFragment("\n").write(o, 0);
    } else {
        return LineStatement(arguments).write(o, 0);
    }
}

/**
 * Creates a new function modeling the function declaration.
 **/
Function
Function::asDeclaration() const {
    auto copy = Function(_returnType, _name, _arguments, nullptr);
    return copy;
}
