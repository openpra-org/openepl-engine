# Base path for test files
set(OPENEPL_TESTS_BASE_PATH "${PROJECT_SOURCE_DIR}/src/test/openepl")

# Test Sources
file(GLOB_RECURSE ALL_FILES ${OPENEPL_TESTS_BASE_PATH}/*.h ${OPENEPL_TESTS_BASE_PATH}/*.cpp)

register_source_groups_from_filestructure("${ALL_FILES}" test)

# Note that the tests also need the source files, except for the main file
include_directories(${GTEST_INCLUDE_DIR})
message(STATUS "Including GoogleTest include dir:" ${GTEST_INCLUDE_DIR})

# Set split and non-split test directories
set(NON_SPLIT_TESTS api storage metrics transformer parser)

function(configure_testsuite_target testsuite)
    message(STATUS CONFIGURING TESTSUITE '${testsuite}') #DEBUG
    target_link_libraries(test-${testsuite} openepl)
    target_link_libraries(test-${testsuite} ${OPENEPL_TEST_LINK_LIBRARIES})

    add_dependencies(test-${testsuite} test-resources)
    add_test(NAME run-test-${testsuite} COMMAND $<TARGET_FILE:test-${testsuite}>)
    add_dependencies(tests test-${testsuite})
endfunction()

foreach(testsuite ${NON_SPLIT_TESTS})
    file(GLOB_RECURSE TEST_${testsuite}_FILES ${OPENEPL_TESTS_BASE_PATH}/${testsuite}/*.h ${OPENEPL_TESTS_BASE_PATH}/${testsuite}/*.cpp)
    add_executable(test-${testsuite} ${TEST_${testsuite}_FILES} ${OPENEPL_TESTS_BASE_PATH}/openepl-test.cpp)
    configure_testsuite_target(${testsuite})
endforeach()
