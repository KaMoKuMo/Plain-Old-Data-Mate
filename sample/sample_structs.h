#pragma once

#include <string>

namespace FakeNamespace {

}
namespace OutterNamespace {
    namespace InnerNamespace {
        struct IntWrapper {
            int64_t i;
        };

        struct Compound {
            IntWrapper wrapper;
            double floatingNumber;
            std::string text;
        };
    }
}

#include "sample_structs_operators.h"
