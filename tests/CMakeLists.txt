# Enable testing and find GTest
enable_testing()

# Test executables
# Phys
add_executable(test_Units test_physlib/test_Units.cpp)
add_executable(test_Utils_phys test_physlib/test_Utils_phys.cpp)
add_executable(test_Trajectories test_physlib/test_Trajectories.cpp)
add_executable(test_ODE_phys test_physlib/test_ODE_phys.cpp)
add_executable(test_Mechanics test_physlib/test_Mechanics.cpp)
add_executable(test_LinearAlgebra_phys test_physlib/test_LinearAlgebra_phys.cpp)
add_executable(test_Control test_physlib/test_Control.cpp)

# Maths
add_executable(test_Utils_math test_mathlib/test_Utils_math.cpp)
add_executable(test_Statistics test_mathlib/test_Statistics.cpp)
add_executable(test_PDE test_mathlib/test_PDE.cpp)
add_executable(test_Optimisation test_mathlib/test_Optimisation.cpp)
add_executable(test_ODE_math test_mathlib/test_ODE_math.cpp)
add_executable(test_LinearAlgebra_math test_mathlib/test_LinearAlgebra_math.cpp)
add_executable(test_Interpolation test_mathlib/test_Interpolation.cpp)
add_executable(test_Integration test_mathlib/test_Integration.cpp)


# Link tests with mathlib / physlib library
set(GTest_DIR "C:/Users/Joss/Documents/Libraries/vcpkg/Installed/x64-windows/share/gtest")
find_package(GTest CONFIG REQUIRED)

# Phys
target_link_libraries(test_Units PRIVATE physlib GTest::gtest_main)
target_link_libraries(test_Utils_phys PRIVATE physlib GTest::gtest_main)
target_link_libraries(test_Trajectories PRIVATE physlib GTest::gtest_main)
target_link_libraries(test_ODE_phys PRIVATE physlib GTest::gtest_main)
target_link_libraries(test_Mechanics PRIVATE physlib GTest::gtest_main)
target_link_libraries(test_LinearAlgebra_phys PRIVATE physlib GTest::gtest_main)
target_link_libraries(test_Control PRIVATE physlib GTest::gtest_main)

# Maths
target_link_libraries(test_Utils_math PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_Statistics PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_PDE PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_Optimisation PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_ODE_math PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_LinearAlgebra_math PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_Interpolation PRIVATE mathlib GTest::gtest_main)
target_link_libraries(test_Integration PRIVATE mathlib GTest::gtest_main)


# Phys
include_directories(test_Units PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)
include_directories(test_Utils_phys PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)
include_directories(test_Trajectories PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)
include_directories(test_ODE_phys PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)
include_directories(test_Mechanics PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)
include_directories(test_LinearAlgebra_phys PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)
include_directories(test_Control PRIVATE ${PROJECT_SOURCE_DIR}/include/physlib)

# Maths
include_directories(test_Utils_math PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_Statistics PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_PDE PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_Optimisation PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_ODE_math PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_LinearAlgebra_math PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_Interpolation PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)
include_directories(test_Integration PRIVATE ${PROJECT_SOURCE_DIR}/include/mathlib)


# Enable test discovery
include(GoogleTest)

# Phys
gtest_discover_tests(test_Units)
gtest_discover_tests(test_Utils_phys)
gtest_discover_tests(test_Trajectories)
gtest_discover_tests(test_ODE_phys)
gtest_discover_tests(test_Mechanics)
gtest_discover_tests(test_LinearAlgebra_phys)
gtest_discover_tests(test_Control)

# Maths
gtest_discover_tests(test_Utils_math)
gtest_discover_tests(test_Statistics)
gtest_discover_tests(test_PDE)
gtest_discover_tests(test_Optimisation)
gtest_discover_tests(test_ODE_math)
gtest_discover_tests(test_LinearAlgebra_math)
gtest_discover_tests(test_Interpolation)
gtest_discover_tests(test_Integration)
