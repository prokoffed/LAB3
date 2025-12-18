cmake_minimum_required(VERSION 3.5)
project(calc)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(calc_lib STATIC src/tarithmeticexpression.cpp)
add_executable(sample_calc samples/sample_calc.cpp)
target_link_libraries(sample_calc calc_lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)