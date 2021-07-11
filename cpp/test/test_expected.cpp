#include <catch2/catch.hpp>

#include "../include/expected.h"
#include "copy_move_tracer.h"

TEST_CASE("Expected - Construction", "[core]") {
    GIVEN("Some Unexpected") {
        using IntTracer = CopyMoveTracer<int>;
        //nicht const wegen damit ein r-value daraus gemacht werden kann
        auto unexpected = Unexpected<IntTracer>(1);
        //Precondition
        REQUIRE(IntTracer::nothingCopiedOrMoved());
        WHEN("The Expected is constructed with an l-value") {
            IntTracer::clear();
            auto const expected = Expected<int, IntTracer>(unexpected);
            THEN("The error is copied once") {
                REQUIRE(IntTracer::totalCount() == 1);
                REQUIRE(IntTracer::copyCtor() == 1);
            }
        }
        WHEN("The Expected is constructed with an r-value") {
            IntTracer::clear();
            auto const expected = Expected<int, IntTracer>(std::move(unexpected));
            THEN("The error is moved once") {
                REQUIRE(IntTracer::totalCount() == 1);
                REQUIRE(IntTracer::moveCtor() == 1);
            }
        }
    }
}

TEST_CASE("Expected - Extracting Values", "[core]") {
    GIVEN("Some Expected storing some expected input value") {
        int const input = 42;
        auto expected = Expected<int, std::string>(input);
        WHEN("The expected is asked whether it holds some expected value") {
            bool const isExpectedValue = static_cast<bool>(expected);
            THEN("the answer should yield true") {
                REQUIRE(isExpectedValue);
            }
        }
        WHEN("The expected is dereferenced") {
            auto const result = *expected;
            THEN("the returned value is the input") {
                REQUIRE(result == input);
            }
        }
        WHEN("The error is demanded") {
            THEN("the expected shall throw") {
                REQUIRE_THROWS(expected.error());
            }
        }
    }
    GIVEN("Some Expected storing some unexpected input value") {
        std::string const input("Ohh, no");
        auto expected = Expected<int, std::string>(Unexpected(input));
        WHEN("The expected is asked wther it holds some expected value") {
            bool const isExpectedValue = static_cast<bool>(expected);
            THEN("the answer should yield false") {
                REQUIRE(!isExpectedValue);
            }
        }
        WHEN("The expected is dereferenced") {
            THEN("the expected shall throw") {
                REQUIRE_THROWS(*expected);
            }
        }
        WHEN("The error is demanded") {
            THEN("the returned value is the stored error") {
                REQUIRE(expected.error() == input);
            }
        }
    }
}

