# PxMLib/Tests/PhysLib_Unit/SingleBodySystemTests/CMakeLists.txt
add_executable(PhysLib_CollisionTests
    main.cpp
    ContactSolverTests.cpp
    ContactTests.cpp
    OBBTests.cpp
    SATTests.cpp
)

target_link_libraries(PhysLib_CollisionTests PRIVATE
    PhysLib
    gtest_main
)

target_include_directories(PhysLib_CollisionTests PRIVATE
    ${COMMON_DIR}
)

include(GoogleTest)

gtest_discover_tests(
    PhysLib_SingleBodySystemTests
    DISCOVERY_MODE PRE_TEST
    DISCOVERY_TIMEOUT 10
)