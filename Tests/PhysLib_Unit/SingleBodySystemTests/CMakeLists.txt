# PxMLib/Tests/PhysLib_Unit/SingleBodySystemTests/CMakeLists.txt
add_executable(PhysLib_SingleBodySystemTests
    main.cpp
    SingleBodySystemDynamicsTests.cpp
)

target_link_libraries(PhysLib_SingleBodySystemTests PRIVATE
    PhysLib
    gtest_main
)

target_include_directories(PhysLib_SingleBodySystemTests PRIVATE
    ${COMMON_DIR}
)

include(GoogleTest)

gtest_discover_tests(
    PhysLib_SingleBodySystemTests
    DISCOVERY_MODE PRE_TEST
    DISCOVERY_TIMEOUT 10
)