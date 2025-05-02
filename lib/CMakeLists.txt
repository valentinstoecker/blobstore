file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/blobstore/*.hpp)

add_library(blobstore SHARED ${SOURCES})
target_include_directories(blobstore PUBLIC include)
target_link_libraries(blobstore PUBLIC ssl)
target_link_libraries(blobstore PRIVATE z)

install(TARGETS blobstore)
install(FILES ${HEADERS} DESTINATION include/blobstore)

add_subdirectory(test)