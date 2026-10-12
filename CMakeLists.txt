cmake_minimum_required(VERSION 3.16)

project(TBN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tbn_reference
    src/reference/gemm.cpp
)

target_include_directories(tbn_reference PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/reference
)

add_executable(test_reference
    tests/test_reference.cpp
)

target_link_libraries(test_reference PRIVATE
    tbn_reference
)

enable_testing()

add_test(NAME reference_gemm COMMAND test_reference)
