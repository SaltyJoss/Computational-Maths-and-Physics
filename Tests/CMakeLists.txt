# PxMLib/Tests/CMakeLists.txt
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Common) # For common test utilities used by both MathLib and PhysLib unit tests
add_subdirectory(MathLib_Unit)
add_subdirectory(PhysLib_Unit)