# CMakeLists.txt for MathLib_Unit_Tests executable
add_executable(MathLib_MatrixUtilsTests
    main.cpp
    MatrixNormTests.cpp
    QuaternionNormTests.cpp
)

target_link_libraries(MathLib_MatrixUtilsTests PRIVATE
    MathLib
    gtest_main
)

target_include_directories(MathLib_MatrixUtilsTests PRIVATE
    ${COMMON_DIR}
)

include(GoogleTest)

gtest_discover_tests(
    MathLib_MatrixUtilsTests
    DISCOVERY_MODE PRE_TEST
    DISCOVERY_TIMEOUT 10
)
