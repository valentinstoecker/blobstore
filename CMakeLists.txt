cmake_minimum_required(VERSION 3.15)

project(blobstore LANGUAGES CXX)



include(CTest)

file(GLOB SOURCES lib/*.cpp)
file(GLOB HEADERS include/blobstore/*.hpp)

add_compile_options(--std=c++20 -Wall -Werror)

add_library(blobstore SHARED ${SOURCES})
target_include_directories(blobstore PUBLIC include)
target_link_libraries(blobstore PRIVATE ssl)

file(GLOB TESTSRC test/*.cpp)

add_executable(blobstore-test ${TESTSRC})
target_link_libraries(blobstore-test blobstore)
target_include_directories(blobstore-test PUBLIC include)

add_test(NAME blobstore-test COMMAND blobstore-test)

install(TARGETS blobstore blobstore-test)
install(FILES ${HEADERS} DESTINATION include)