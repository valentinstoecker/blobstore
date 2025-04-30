cmake_minimum_required(VERSION 3.15)

project(blobstore LANGUAGES CXX)

add_compile_options(--std=c++20 -Wall -Werror)
add_subdirectory(lib)

include(CTest)

add_subdirectory(test)
