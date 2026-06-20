# CMakeLists.txt for PxMLib project
cmake_minimum_required(VERSION 3.17)
project(PxMLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

set(OUTPUT_BASE ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE}/lib)

include(FetchContent)

# --- External Dependencies ---
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 5.0.0
)
FetchContent_MakeAvailable(eigen)

# --- Subdirectories ---
add_subdirectory(MathLib)
add_subdirectory(PhysLib)

option(PXMLIB_BUILD_TESTS "Build PxMLib tests" OFF)

if(PXMLIB_BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_subdirectory(Tests)
endif()

