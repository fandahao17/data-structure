cmake_minimum_required(VERSION 3.10)
project(data_structure)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(TryString TryString.cpp)
add_executable(Hello Hello.cpp)
add_executable(Debugging Debugging.cpp)