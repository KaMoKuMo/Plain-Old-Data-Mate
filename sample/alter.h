#pragma once

#include "sample_structs.h"

namespace OutterNamespace::InnerNamespace {
    void
    alter(IntWrapper& wrapper) {
        wrapper.i  -= 1;
    }

    void
    alter(Compound& compound) {
        compound.floatingNumber += 3.21;
    }
}
