
//! type trait to deduce the contained error type. If the type is not an Expected type, the type is void (the only not allowed error type)
template<typename T, typename = void> struct expected_single_error_type { using type = void; }; //the only type not allowed as an error -> not an expected
template<typename T, typename E> struct expected_single_error_type<Expected<T, E>> { using type = E; };
template<typename T, typename E> struct expected_single_error_type<Expected<T, E> const> { using type = E; };
template<typename T, typename E> struct expected_single_error_type<Expected<T, E> volatile> { using type = E; };
template<typename T> using expected_single_error_type_t = typename expected_single_error_type<std::remove_reference_t<T>>::type;

//! helper trait to deduce first error type of some arbitrary arguments (one of them has to be an Expected type)
template<typename ...Ts> struct expected_error_type;
template<typename T> struct expected_error_type<T>{ using type = expected_single_error_type_t<T>; };
template<typename T, typename S, typename ...Ts>
struct expected_error_type<T, S, Ts...>{ using type = std::conditional_t<is_expected_v<std::remove_reference_t<T>>,
                                                                         expected_single_error_type_t<T>,
                                                                         typename expected_error_type<S, Ts...>::type>; };
template<typename ...Ts>
using expected_error_type_t = typename expected_error_type<Ts...>::type;

//! Helper functions to check whether some type is an expected type and contains a value. (alwalys false if the type is not an expected type)
template<typename T>
constexpr bool containsError(T const&) { return false; };
template<typename T, typename E>
constexpr bool containsError(Expected<T, E> const& ex) { return !ex; };
//! Checks whether an arbitary number of arguments contains any error
template<typename ...Ts>
constexpr bool anyContainsError(Ts const& ...ts) { return (containsError(ts) || ...); }

//! Base case <- this should never be called.
template<typename ErrorType>
constexpr auto extractError() { return ErrorType{}; }
//! Tries to find the Expected containing an error and returning it.
template<typename ErrorType, typename T, typename ...Ts>
constexpr auto extractError(T&& t, Ts&& ...ts) {
    if constexpr (is_expected_v<std::remove_reference_t<T>>) {
        if (!t) {
            return std::move(t).error();
        }
    } 
    return extractError<ErrorType>(std::forward<Ts>(ts)...);
}

//! Calls f base case
template<typename Function>
auto callUnpacked(Function f) {
    return f();
}
//! Unpacks any Expected type (blindly assuming it is the expected value)
template<typename Function, typename T, typename ...Ts>
auto callUnpacked(Function f, T&& t, Ts&& ...ts) {
    auto withNextCaputured = [&]() {
        if constexpr (is_expected_v<std::remove_reference_t<T>>) {
            return [&](auto&& ...otherArgs) { return f(*std::forward<T>(t), std::forward<decltype(otherArgs)>(otherArgs)...); };
        } else {
            return [&](auto&& ...otherArgs) { return f(std::forward<T>(t), std::forward<decltype(otherArgs)>(otherArgs)...); };
        }
    }();
    return callUnpacked(withNextCaputured, std::forward<Ts>(ts)...);
}
