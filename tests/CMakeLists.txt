enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

# --- PhysLib tests ---
file(GLOB PHYS_TEST_SOURCES test_physlib/*.cpp)
list(APPEND TEST_SOURCES ${PHYS_TEST_SOURCES})

# --- MathLib tests ---
file(GLOB MATH_TEST_SOURCES test_mathlib/*.cpp)
list(APPEND TEST_SOURCES ${MATH_TEST_SOURCES})

# --- Test executable ---
add_executable(UnitTests test_main.cpp ${TEST_SOURCES})

# --- Link libraries ---
target_link_libraries(UnitTests PRIVATE physlib mathlib GTest::gtest_main)

# --- Include directories ---
target_include_directories(UnitTests PRIVATE
    ${PROJECT_SOURCE_DIR}/include/physlib
    ${PROJECT_SOURCE_DIR}/include/mathlib
)

# --- Register tests with CTest ---
gtest_discover_tests(UnitTests)
