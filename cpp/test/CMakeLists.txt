# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(
    unittests
    constexpr_test_expected_invoke.cpp
    test_expected.cpp
    test_expected_invoke.cpp
    test_convert_command_line_arguments.cpp
    test_extract_struct_snippets.cpp
    test_partition_into_struct_strings.cpp
    test_write_equal_operator.cpp
)

target_link_libraries(
    unittests
    PRIVATE
        catch_main
        project_options
        podmateLib
)

#add_test(unittests unittests)
# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to
# whatever you want, or use different for different binaries
catch_discover_tests(
  unittests
  TEST_PREFIX
  "unittests."
)
