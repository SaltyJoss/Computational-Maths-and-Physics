include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Correct path: CMakeLists.txt is inside 'tests/' already
add_executable(test_ExplicitSolvers
    test_ExplicitSolvers.cpp
)

add_executable(test_integrators
    test_integrators.cpp
)

# Link against library and gtest
target_link_libraries(test_ExplicitSolvers PRIVATE mathlib gtest_main)
target_link_libraries(test_integrators PRIVATE mathlib gtest_main)

# Include headers from main include folder
target_include_directories(test_ExplicitSolvers PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(test_integrators PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Enable test discovery
include(GoogleTest)
gtest_discover_tests(test_ExplicitSolvers)
gtest_discover_tests(test_integrators)