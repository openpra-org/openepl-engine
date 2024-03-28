cmake_minimum_required(VERSION 3.12)

# set the project name and version
project(openepl-engine VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the resources/cmake folder to Module Search Path for FindTBB.cmake
set(CMAKE_MODULE_PATH   ${CMAKE_MODULE_PATH}
                        "${PROJECT_SOURCE_DIR}/resources/cmake/find_modules"
                        "${PROJECT_SOURCE_DIR}/resources/cmake/macros")

include(ExternalProject)
include(RegisterSourceGroup)
include(imported)

#############################################################
##
##	Include the targets for non-system resources
##
#############################################################

# In 3rdparty, targets are being defined that can be used
# in the the system does not have a library
include(resources/3rdparty/CMakeLists.txt)

# Include Doxygen
include(resources/doxygen/CMakeLists.txt)

# Add base folder for better inclusion paths
include_directories("${PROJECT_SOURCE_DIR}/src")

#############################################################
##
##	Storm
##
#############################################################

set(STORM_DEVELOPER ON)
set(STORM_USE_INTELTBB OFF)

message(STATUS "STORM_DEVELOPER: ${STORM_DEVELOPER}")


set(storm_DIR /opt/storm/build)
find_package(storm REQUIRED)
message(STATUS "Storm include directory: ${storm_INCLUDE_DIR}")
file(COPY ${storm_INCLUDE_DIR} DESTINATION include)
file(COPY ${storm-parsers_INCLUDE_DIR} DESTINATION include)
file(COPY ${storm-conv_INCLUDE_DIR} DESTINATION include)
file(COPY ${storm-dft_INCLUDE_DIR} DESTINATION include)
set(OPENEPL_LINK_LIBRARIES storm storm-parsers storm-conv storm-dft api transformer storage parser)

# Directory for test resources.
set(OPENEPL_TEST_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/resources/examples/testfiles")


# Add the binary dir include directory for openepl-config.h
include_directories("${PROJECT_BINARY_DIR}/include")

include(CTest)
# Compiles all tests
add_custom_target(tests)
# Compiles and runs all tests
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
set(CMAKE_CTEST_COMMAND_VERBOSE ${CMAKE_CTEST_COMMAND} -V)
add_custom_target(check-verbose COMMAND ${CMAKE_CTEST_COMMAND_VERBOSE})
add_dependencies(check tests)
add_dependencies(check-verbose tests)
# Apply code formatting
add_custom_target(format COMMAND ${PROJECT_SOURCE_DIR}/resources/scripts/auto-format.sh)

set(OPENEPL_TARGETS "")
add_subdirectory(src)


include(OpenEPLCPackConfig.cmake)

# Configure a header file to pass some of the CMake settings to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/openepl-config.h.in"
        "${PROJECT_BINARY_DIR}/include/openepl-config.h"
)

# specify source files
set(SOURCE_FILES    src/main.cpp)

message(OPENEPL_LINK_LIBRARIES ${OPENEPL_LINK_LIBRARIES})

# set executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_FILES} include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENEPL_LINK_LIBRARIES})
