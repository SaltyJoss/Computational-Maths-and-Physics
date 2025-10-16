# Specify the minimum CMake version and project info
cmake_minimum_required(VERSION 3.15)
project(MathLib LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library
add_library(mathlib
    ${PROJECT_SOURCE_DIR}/src/ODESolver.cpp
)

# Tell CMake where to find headers when building and using the library
target_include_directories(mathlib 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Add the tests folder
enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)