

add_executable(
    cli
    src/main.cpp
)

target_link_libraries(
    cli
    PRIVATE
        project_options
        project_warnings
)
