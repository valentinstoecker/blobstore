cmake_minimum_required(VERSION 3.15)

project(blobstore LANGUAGES CXX)

file(GLOB SOURCES lib/*.cpp)
file(GLOB HEADERS include/blobstore/*.hpp)

add_compile_options(--std=c++20 -Wall -Werror)

add_library(blobstore SHARED ${SOURCES})
target_include_directories(blobstore PUBLIC include)
target_link_libraries(blobstore PUBLIC ssl)

file(GLOB TESTSRC test/*.cpp)

add_executable(blobstore-test ${TESTSRC})
target_link_libraries(blobstore-test PRIVATE blobstore)
#target_include_directories(blobstore-test PUBLIC include)

include(CTest)
enable_testing()
add_test(NAME blobstore COMMAND blobstore-test)

install(TARGETS blobstore blobstore-test)
install(FILES ${HEADERS} DESTINATION include)