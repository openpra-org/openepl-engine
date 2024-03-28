set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_target(binaries)

add_subdirectory(api)
add_subdirectory(parser)
add_subdirectory(storage)
add_subdirectory(transformer)
add_subdirectory(utility)

#if (OPENEPL_EXCLUDE_TESTS_FROM_ALL)
#    add_subdirectory(test EXCLUDE_FROM_ALL)
#else()
#    add_subdirectory(test)
#endif()

set(OPENEPL_TARGETS ${OPENEPL_TARGETS} PARENT_SCOPE)
