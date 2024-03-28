#############################################################
##
##	Boost
##
#############################################################

# Boost Option variables
set(Boost_USE_STATIC_LIBS ${USE_BOOST_STATIC_LIBRARIES})
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_BOOST_CMAKE ON)

find_package(Boost 1.61.0 QUIET REQUIRED COMPONENTS filesystem system)
if (NOT Boost_FOUND)
    if (Boost_VERSION)
        message(FATAL_ERROR "The required Boost version is 1.61.0 or newer, however, only ${Boost_VERSION} was found.")
    else ()
        message(FATAL_ERROR "Boost was not found.")
    endif ()
endif ()
if ((NOT Boost_LIBRARY_DIRS) OR ("${Boost_LIBRARY_DIRS}" STREQUAL ""))
    set(Boost_LIBRARY_DIRS "${Boost_INCLUDE_DIRS}/stage/lib")
endif ()

set(CNTVAR 3)
foreach(BOOSTLIB ${Boost_LIBRARIES})
    add_imported_library(target-boost-${CNTVAR} SHARED ${BOOSTLIB} ${Boost_INCLUDE_DIRS})
    list(APPEND OPENEPL_DEP_TARGETS target-boost-${CNTVAR}_SHARED)
    MATH(EXPR CNTVAR "${CNTVAR}+1")
endforeach()
message(STATUS "OpenEPL - Storm - Using boost ${Boost_VERSION} (library version ${Boost_LIB_VERSION}).")
# set the information for the config header
set(OPENEPL_BOOST_INCLUDE_DIR "${Boost_INCLUDE_DIRS}")