#pragma once

#include "expected.h"
#include "expected_invoke_helper.h"

/** \addtogroup core
 * @{
 */

/**
 * Helper function to reduce error-checking logic.
 * This function first checks whether some expected argument contains
 * the unexpected value.
 * If so this functions returns this error as the error, else it
 * returns the invocation result of the passed in function - called with the
 * unpacked arguments.
 *
 * @code
 * auto sum = [](int lhs, int rhs){ return lhs + rhs; };
 * auto expected = Expected<int, std::string>(42); //<- contains an expected value
 * auto unexpected = Expected<int, std::string>(Unexpected(std::string("oh, no!")));
 *
 * auto result1 = expected_invoke(sum, expected, unexpected); //<- this will not invoke sum, but return the error
 * auto result2 = expected_invoke(sum, expected, 2); //<- since no value is unexpected invokes sum -> returns 44
 * auto result3 = expected_invoke(sum, 2, expected); //<- since no value is unexpected invokes sum -> returns 44
 * //auto result4 = expected_invoke(sum, 2, 42); //<- will not compile since no arguments is an Expected
 *
 * @endcode
 *
 * It is required that all the error types of the passed in arguments (of those which are of any Expected<T, E_i>),
 * are convertible into each other.
 *
 * If the "to-be-invoked-function", f, would return some expected, Expected<T, E2> the return type
 * is collapsed, requiring that the error types of the arguments are also
 * convertible into the error type of the function "f".
 *
 * @code
 * auto answer = [](int param) -> Expected<std::string, std::string>{ return param == 42 ? std::string("good") : Unexpected(std::string("bad")); };
 * auto expected = Expected<int, std::string>(12);
 * auto unexpected = Expected<int std::string>(Unexpected("oh, no"));
 *
 * auto result1 = expected_invoke(answer, expected); //<- will invoke the function, but returns an unexpected due to the function answer itself
 * static_assert(std::is_same_v<decltype(result1), Expected<std::string, std::string>>);
 *
 * auto result2 = expected_invoke(answer, unexpected); //<- will not invoke the function but return the original error
 *
 * //auto result3 = expected_invoke(answer, Expected<int, int>(42)); //<- will not compile because the error of the argument wouldn't be convertible into the error type of the function to be invoked
 * @endcode
 *
 * \param f, function to be invoked,
 * \param args..., any number of Arguments. One of them has to be an Expected type.
 *
 **/
template<typename Function,
         typename ...Args,
         typename FunctionReturnType = decltype(callUnpacked(std::declval<Function>(), std::declval<Args&&>()...)),
         typename InputArgumentErrorType = expected_error_type_t<Args...>,
         typename ReturnType = std::conditional_t<is_expected_v<FunctionReturnType>,
                                                     FunctionReturnType,
                                                     Expected<FunctionReturnType, InputArgumentErrorType>>>
ReturnType
expected_invoke(Function f, Args&& ...args) {
    if (anyContainsError(args...)) {
        return Unexpected(extractError<InputArgumentErrorType>(std::forward<Args>(args)...));
    }
    if constexpr (std::is_same_v<void, FunctionReturnType>) {
        callUnpacked(f, std::forward<Args>(args)...);
        return {};
    } else {
        return callUnpacked(f, std::forward<Args>(args)...);
    }
}
/** @} */

