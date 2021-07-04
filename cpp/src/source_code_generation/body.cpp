#include "source_code_generation/body.h"
#include "source_code_generation/line_fragment.h"

Body::Body(std::unique_ptr<SourceCode> body)
    :_body(std::move(body))
{
}

std::ostream&
Body::write(std::ostream& o, size_t indentationLevel) const {
    o << " {\n";
    if (_body) {
        _body->write(o, indentationLevel + 1);
    }
    return LineFragment(std::string("}")).write(o, indentationLevel);
}
