add_custom_target(resources)
add_custom_target(test-resources)

set(OPENEPL_3RDPARTY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/resources/3rdparty)
set(OPENEPL_3RDPARTY_BINARY_DIR ${PROJECT_BINARY_DIR}/resources/3rdparty)
set(OPENEPL_3RDPARTY_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include/resources/3rdparty)

message(STATUS "OpenEPL - Building external resources with ${OPENEPL_RESOURCES_BUILD_JOBCOUNT} job(s) in parallel.")

include(resources/3rdparty/boost/CMakeLists.txt)
include(resources/3rdparty/l3pp/CMakeLists.txt)
include(resources/3rdparty/carl/CMakeLists.txt)
include(resources/3rdparty/googletest/CMakeLists.txt)
