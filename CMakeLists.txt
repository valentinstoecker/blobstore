cmake_minimum_required(VERSION 3.15)

project(blobstore LANGUAGES CXX)

add_compile_options(--std=c++20 -Wall -Werror)

include(CTest)

add_subdirectory(lib)
