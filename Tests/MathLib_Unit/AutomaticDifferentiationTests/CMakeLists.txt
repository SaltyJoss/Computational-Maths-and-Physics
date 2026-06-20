# PxMLib/Tests/MathLib_Unit/AutomaticDifferentiationTests/CMakeLists.txt
enable_testing()

add_executable(MathLib_ADTests
    main.cpp
    ADNewtonTests.cpp
    ADJacobianTests.cpp
    ADExplicitIntegratorTests.cpp
    ADImplicitIntegratorTests.cpp
)

target_link_libraries(MathLib_ADTests PRIVATE
    MathLib
    gtest_main
)

target_include_directories(MathLib_ADTests PRIVATE
    ${COMMON_DIR}
)

include(GoogleTest)

gtest_discover_tests(
    MathLib_ADTests
    DISCOVERY_MODE PRE_TEST
    DISCOVERY_TIMEOUT 10
)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     gtest_discover_tests(
#         MathLib_DualNumberTests
#         DISCOVERY_MODE PRE_TEST
#         DISCOVERY_TIMEOUT 10
#     )
# else()
#     gtest_discover_tests(MathLib_DualNumberTests)
# endif()
