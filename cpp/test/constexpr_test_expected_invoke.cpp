#include "expected.h"

#include "expected_invoke.h"


static_assert(std::is_same_v<int, expected_value_type_t<Expected<int, char>>>);
static_assert(std::is_same_v<int, expected_value_type_t<Expected<int, char>&&>>);
static_assert(std::is_same_v<int, expected_value_type_t<Expected<int, char> const&>>);
static_assert(std::is_same_v<int, expected_value_type_t<Expected<int, char> volatile&&>>);

static_assert(std::is_same_v<void, expected_single_error_type_t<int>>);
static_assert(std::is_same_v<char, expected_single_error_type_t<Expected<int, char>>>);
static_assert(std::is_same_v<char, expected_single_error_type_t<Expected<int, char>&&>>);
static_assert(std::is_same_v<char, expected_single_error_type_t<Expected<int, char> const>>);
static_assert(std::is_same_v<char, expected_single_error_type_t<Expected<int, char> volatile>>);

template<typename ...Ts> auto echo(Ts...){ return 42;}
static_assert(std::is_same_v<Expected<int, char>, decltype(expected_invoke(echo<int>, std::declval<Expected<int, char>>()))>);
static_assert(std::is_same_v<Expected<int, char>, decltype(expected_invoke(echo<int, int, double>, std::declval<int>(), std::declval<Expected<int, char>>(), std::declval<double>()))>);
