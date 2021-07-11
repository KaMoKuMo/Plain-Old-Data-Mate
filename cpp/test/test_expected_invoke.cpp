#include <catch2/catch.hpp>

#include "expected_invoke.h"
#include "copy_move_tracer.h"

TEST_CASE("expected_invoke", "[core]") {
    GIVEN("some function taking a single argument") {
        bool hasBeenCalled = false;
        auto echo = [&](int i) { hasBeenCalled = true;};
        WHEN("expected_invoke is called with some filled expected") {
            auto const result = expected_invoke(echo, Expected<int, char>(42));
            THEN("the function has been called") {
                REQUIRE(hasBeenCalled);
            }
            THEN("the returned expected contains a success") {
                REQUIRE(static_cast<bool>(result));
            }
        }
    }
    GIVEN("some function taking two argoments") {
        auto sink = [](int, int){};
        WHEN("expected_invoke is called with the second argument being an unexpected") {
            auto const result = expected_invoke(sink, 42, Expected<int, char>(Unexpected('a')));
            THEN("the returned value is an error") {
                REQUIRE(!result);
            }
            THEN("the error is propagated") {
                REQUIRE(result.error() == 'a');
            }
        }
        WHEN("expected_invoke is called with the first one being expected but the second one unexpected") {
            auto const result = expected_invoke(sink, Expected<int, char>(42), Expected<int, char>(Unexpected('a')));
            THEN("the returned value is an error") {
                REQUIRE(!result);
            }
            THEN("the error is propagated") {
                REQUIRE(result.error() == 'a');
            }
        }
    }
    GIVEN("some function requiring a copy-move-tracer") {
        auto sink = [](CopyMoveTracer<int>){};
        WHEN("expected_invoke is called with some r-value expected") {
            auto const result = expected_invoke(sink, Expected<CopyMoveTracer<int>, char>(42));
            THEN("The CopyMoveTracer does not record any copying") {
                REQUIRE(CopyMoveTracer<int>::copyCtor() == 0);
                REQUIRE(CopyMoveTracer<int>::copyAssignment() == 0);
            }
        }
    }
}
