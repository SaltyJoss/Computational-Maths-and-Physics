# Root CMakeList
cmake_minimum_required(VERSION 3.15)
project(MathLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE MATHLIB_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(mathlib STATIC ${MATHLIB_SOURCES})

target_include_directories(mathlib 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(mathlib PRIVATE -Wall -Wextra -O2)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)