# cmake_minimum_required(VERSION 3.10)
# project(FuncFactory)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_executable(FuncFactory main.cpp Functions.cpp)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

set(Function Factory.hpp Functions.hpp Functions.cpp)

add_library(Functions ${Function})
add_executable(functions tests/Polynomial.cpp tests/Exponential.cpp tests/Arithmetic.cpp)

target_link_libraries(functions Functions)
target_link_libraries(functions gtest_main)
add_test(NAME functions COMMAND functions)