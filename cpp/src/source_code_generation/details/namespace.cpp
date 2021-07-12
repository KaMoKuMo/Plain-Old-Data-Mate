#include "source_code_generation/details/namespace.h"
#include "source_code_generation/details/line_fragment.h"

Namespace::Namespace(std::string name,
                     Body body)
    : _name(name)
    , _body(std::move(body))
{
}

std::ostream&
Namespace::write(std::ostream& o, size_t indentationLevel) const {
    LineFragment("namespace " + _name).write(o, indentationLevel);
    _body.write(o, indentationLevel);
    return LineFragment("\n").write(o, 0);
}

