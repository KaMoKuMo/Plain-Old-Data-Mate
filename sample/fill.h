#pragma once

#include "sample_structs.h"

namespace OutterNamespace::InnerNamespace {

inline void
fill(IntWrapper& wrapper) {
    wrapper.i = 32;
}

inline void
fill(Compound& compound) {
    compound.wrapper.i = 52;
    compound.floatingNumber = -21.23;
    compound.text = "sample";
}

}
