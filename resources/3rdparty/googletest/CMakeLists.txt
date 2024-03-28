#############################################################
##
##	Google Test gtest
##
#############################################################
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    # Fetch the content using previously declared details
    FetchContent_Populate(googletest)
    # Bring the populated content into the build
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Specify directories
set(googletest_INCLUDE_DIR ${googletest_SOURCE_DIR}/googletest/include)
set(GTEST_INCLUDE_DIR ${googletest_INCLUDE_DIR})
set(GTEST_BIN_DIR ${googletest_BINARY_DIR})
set(GTEST_LIB_DIR ${googletest_BINARY_DIR})

# Specify MainTest's link libraries
set(GTEST_LIBRARIES gtest gtest_main)

add_dependencies(test-resources gtest)
list(APPEND OPENEPL_TEST_LINK_LIBRARIES ${GTEST_LIBRARIES})