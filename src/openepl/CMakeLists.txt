# TODO:: Include all files one by one
file(GLOB_RECURSE ALL_FILES ${PROJECT_SOURCE_DIR}/src/openepl/*.h ${PROJECT_SOURCE_DIR}/src/openepl/*.cpp)

register_source_groups_from_filestructure("${ALL_FILES}" openepl)

#############################################################
##
##	Source file aggregation and clustering
##
#############################################################
file(GLOB_RECURSE OPENEPL_HEADERS ${PROJECT_SOURCE_DIR}/src/openepl/*.h)
file(GLOB_RECURSE OPENEPL_SOURCES_WITHOUT_MAIN ${PROJECT_SOURCE_DIR}/src/openepl/*/*.cpp)
file(GLOB_RECURSE OPENEPL_HEADERS_WITHOUT_MAIN ${PROJECT_SOURCE_DIR}/src/openepl/*/*.h)
file(GLOB_RECURSE OPENEPL_MAIN_FILE ${PROJECT_SOURCE_DIR}/src/openepl/openepl.cpp)

# Additional include files like the storm-config.h
file(GLOB_RECURSE OPENEPL_BUILD_HEADERS ${PROJECT_BINARY_DIR}/include/*.h)

set(OPENEPL_LIB_SOURCES ${OPENEPL_3RDPARTY_SOURCES} ${OPENEPL_SOURCES_WITHOUT_MAIN})
set(OPENEPL_LIB_HEADERS ${OPENEPL_HEADERS} ${OPENEPL_HEADERS_WITHOUT_MAIN})
set(OPENEPL_MAIN_SOURCES  ${OPENEPL_MAIN_FILE})


###############################################################################
##
##	Binary creation (All link_directories() calls must be made before this point.)
##
###############################################################################

# Create libstorm.
add_library(openepl SHARED ${OPENEPL_LIB_SOURCES} ${OPENEPL_LIB_HEADERS})
# Remove define symbol for shared libstorm.
set_target_properties(openepl PROPERTIES DEFINE_SYMBOL "")

#The library that needs symbols must be first, then the library that resolves the symbol.
message(STATUS "OPENEPL_LINK_LIBRARIES: ${OPENEPL_LINK_LIBRARIES}")
target_link_libraries(openepl PUBLIC ${OPENEPL_DEP_TARGETS} ${OPENEPL_DEP_IMP_TARGETS} ${OPENEPL_LINK_LIBRARIES})
list(APPEND OPENEPL_TARGETS openepl)
set(OPENEPL_TARGETS ${OPENEPL_TARGETS} PARENT_SCOPE)

# Create openepl.
add_executable(openepl-cli ${OPENEPL_MAIN_SOURCES} ${OPENEPL_MAIN_HEADERS})
target_link_libraries(openepl-cli PUBLIC openepl ${OPENEPL_DEP_TARGETS} ${OPENEPL_DEP_IMP_TARGETS} ${OPENEPL_LINK_LIBRARIES})
set_target_properties(openepl-cli PROPERTIES OUTPUT_NAME "openepl-cli")

# Install openepl headers to include directory.
foreach(HEADER ${OPENEPL_LIB_HEADERS})
    string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/src/?" "" RELATIVE_HEADER_PATH ${HEADER})
    string(REGEX MATCH "(.*)[/\\]" RELATIVE_DIRECTORY ${RELATIVE_HEADER_PATH})
    string(REGEX REPLACE "${RELATIVE_DIRECTORY}/?" "" HEADER_FILENAME ${RELATIVE_HEADER_PATH})
    add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/include/${RELATIVE_DIRECTORY}${HEADER_FILENAME}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/${RELATIVE_DIRECTORY}
            COMMAND ${CMAKE_COMMAND} -E copy ${HEADER} ${CMAKE_BINARY_DIR}/include/${RELATIVE_DIRECTORY}${HEADER_FILENAME}
            DEPENDS ${HEADER}
    )
    list(APPEND OPENEPL_OUTPUT_HEADERS "${CMAKE_BINARY_DIR}/include/${RELATIVE_DIRECTORY}${HEADER_FILENAME}")
endforeach()
add_custom_target(copy_openepl_headers DEPENDS ${OPENEPL_OUTPUT_HEADERS} ${OPENEPL_LIB_HEADERS})
add_dependencies(openepl copy_openepl_headers)

add_dependencies(binaries openepl-cli)

# installation
install(TARGETS openepl EXPORT openepl_Targets RUNTIME DESTINATION bin LIBRARY DESTINATION lib)
install(TARGETS openepl-cli EXPORT openepl_Targets RUNTIME DESTINATION bin LIBRARY DESTINATION lib OPTIONAL)
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION include/openepl
        FILES_MATCHING PATTERN "*.h")
