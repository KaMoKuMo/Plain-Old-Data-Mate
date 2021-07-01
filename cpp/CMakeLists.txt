

add_executable(
    podmate
    src/main.cpp
)

target_link_libraries(
    podmate
    PRIVATE
        project_options
        project_warnings
        CONAN_PKG::docopt.cpp
)

if(ENABLE_TESTING)
   add_subdirectory(test)
endif()
