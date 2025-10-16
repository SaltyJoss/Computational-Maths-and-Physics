# Enable testing
enable_testing()

# Test executables
add_executable(test_ExplicitSolvers
    test_ExplicitSolvers.cpp
)

add_executable(test_integrators
    test_integrators.cpp
)

# Link the test executables with the mathlib library and Google Test
find_package(GTest CONFIG REQUIRED)
target_link_libraries(test_ExplicitSolvers PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_integrators PRIVATE mathlib GTest::gtest_main)

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