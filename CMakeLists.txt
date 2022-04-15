cmake_minimum_required(VERSION 3.12)

# set the project name and version
project(openepl-engine VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#############################################################
##
##	CMake options
##
#############################################################
message(STORM_DEVELOPER:  ${STORM_DEVELOPER})

set(storm_DIR /opt/storm/build)
find_package(storm REQUIRED)
message(Storm include directory: ${storm_INCLUDE_DIR} ${storm-parsers_INCLUDE_DIR})

# specify source files
set(SOURCE_FILES src/main)

# set executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_FILES} ${storm_INCLUDE_DIR} ${storm-parsers_INCLUDE_DIR} include)
target_link_libraries(${PROJECT_NAME} PRIVATE storm storm-parsers)

