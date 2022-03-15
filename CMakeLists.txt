cmake_minimum_required(VERSION 3.12)

# set the project name and version
project(openerror-pro-engine VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# search for Storm library
# Add the resources/cmake folder to Module Search Path for FindTBB.cmake
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/resources/cmake/find_modules")
# set(STORM_DIR "${PROJECT_SOURCE_DIR}/src/storm")

# message(${STORM_DIR})
add_subdirectory(src/storm)
#find_package(storm REQUIRED)

# specify source files
set(SOURCE_FILES src/main.cpp)

# set executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_FILES} ${storm_INCLUDE_DIR} ${storm-parsers_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE storm storm-parsers)

