#include "source_code_generation/line_fragment.h"


LineFragment::LineFragment(std::string initalData)
    : _lineFragment(initalData)
{
}

/**
 * \param additionalData to be appended on \see _lineFragment
 **/
LineFragment&
LineFragment::append(std::string additionalData) {
    _lineFragment += additionalData;
    return *this;
}

std::ostream&
LineFragment::write(std::ostream& o, size_t indentationLevel) const {
    return o << std::string(indentationLevel * 4,  ' ') << _lineFragment;
}
