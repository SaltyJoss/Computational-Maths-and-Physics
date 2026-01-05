cmake_minimum_required(VERSION 3.15)
project(PxM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ====== Source discovery ======
file(GLOB_RECURSE MATHLIB_SOURCES
    "${PROJECT_SOURCE_DIR}/src/mathlib/*.cpp"
)

file(GLOB_RECURSE PHYSLIB_SOURCES
    "${PROJECT_SOURCE_DIR}/src/physlib/*.cpp"
)

# ====== Library targets ======
add_library(mathlib STATIC ${MATHLIB_SOURCES})
add_library(physlib STATIC ${PHYSLIB_SOURCES})

target_include_directories(mathlib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ====== Main executable ======
add_executable(Main "${CMAKE_SOURCE_DIR}/src/Main.cpp")
target_link_libraries(Main PRIVATE mathlib physlib)

# ====== Compiler warnings ======
target_compile_options(mathlib PRIVATE /W4 /permissive-)
target_compile_options(physlib PRIVATE /W4 /permissive-)

# --- Tests ---
enable_testing()
add_subdirectory(tests)
