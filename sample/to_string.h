#pragma once

#include "sample_structs.h"

#include <string>
#include <sstream>

template<typename T>
std::string
toStringThroughStream(T t) {
    std::stringstream stream;
    stream << t;
    return stream.str();
}

namespace OutterNamespace::InnerNamespace {

    inline std::string
    toString(IntWrapper const& wrapper) {
        return std::string("{ \"i\" : " + toStringThroughStream(wrapper.i) + " }");
    }

    inline std::string
    toString(Compound const& compound) {
        return std::string("{ \"wrapper\" : " + toString(compound.wrapper) + ", \"floatingNumber\" : " + toStringThroughStream(compound.floatingNumber) + " }");
    }
}
