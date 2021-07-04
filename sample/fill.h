#pragma once

#include "sample_structs.h"

inline void
fill(IntWrapper& wrapper) {
    wrapper.i = 32;
}

inline void
fill(Compound& compound) {
    compound.wrapper.i = 52;
    compound.floatingNumber = -21.23;
}
