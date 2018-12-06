cmake_minimum_required(VERSION 3.9)
project(a4tasks)

set(CMAKE_CXX_STANDARD 11)
file(GLOB src_cpp_files "src/*.cpp")

add_executable(a4tasks ${src_cpp_files})
target_link_libraries(a4tasks pthread)