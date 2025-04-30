file(GLOB TESTSRC *.cpp)
add_executable(blobstore-test ${TESTSRC})
target_link_libraries(blobstore-test PRIVATE blobstore)

add_test(NAME blobstore COMMAND blobstore-test)