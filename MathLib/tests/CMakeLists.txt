# Enable testing
enable_testing()

# Find Google Test
find_package(GTest CONFIG REQUIRED)

# -------------------------------
# Math Tests
# -------------------------------
file(GLOB_RECURSE MATH_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/math/*.cpp")

foreach(test_src ${MATH_TEST_SOURCES})
    # Get the file name without extension
    get_filename_component(test_name ${test_src} NAME_WE)

    # Add executable
    add_executable(${test_name} ${test_src})

    # Link to mathlib and GTest
    target_link_libraries(${test_name} PRIVATE mathlib GTest::gtest_main)

    # Include headers
    target_include_directories(${test_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    # Discover and register tests with label "math"
    gtest_discover_tests(${test_name} LABELS math)
endforeach()

# -------------------------------
# Physics Tests
# -------------------------------
file(GLOB_RECURSE PHYS_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/phys/*.cpp")

foreach(test_src ${PHYS_TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE mathlib GTest::gtest_main)
    target_include_directories(${test_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    gtest_discover_tests(${test_name} LABELS phys)
endforeach()
