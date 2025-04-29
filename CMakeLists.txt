cmake_minimum_required(VERSION 3.15)

project(blobstore LANGUAGES CXX)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/blobstore/*.hpp)

add_library(blobstore SHARED ${SOURCES})
target_include_directories(blobstore PUBLIC include)
target_link_libraries(blobstore PRIVATE ssl)

install(TARGETS blobstore)
install(FILES ${HEADERS} DESTINATION include)