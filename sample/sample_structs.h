#pragma once

namespace FakeNamespace {

}

namespace OutterNamespace {
    namespace InnerNamespace {
        struct IntWrapper {
            int i;
        };

        struct Compound {
            IntWrapper wrapper;
            double floatingNumber;
        };
    }
}

#include "sample_structs_operators.h"
