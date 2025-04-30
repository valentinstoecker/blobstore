file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_library(blobstore SHARED ${SOURCES})
target_include_directories(blobstore PUBLIC include)
target_link_libraries(blobstore PUBLIC ssl)

install(TARGETS blobstore)
install(FILES ${HEADERS} DESTINATION include)