#############################################################
##
##	l3pp
##
#############################################################
FILE(REMOVE_RECURSE ${OPENEPL_3RDPARTY_INCLUDE_DIR}/l3pp)

# Do not take a branch, needs internet connection.
ExternalProject_Add(
        l3pp_ext
        GIT_REPOSITORY https://github.com/hbruintjes/l3pp.git
        GIT_TAG e4f8d7fe6c328849aff34d2dfd6fd592c14070d5
        PREFIX ${OPENEPL_3RDPARTY_INCLUDE_DIR}/l3pp
        UPDATE_COMMAND ""
        CMAKE_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        TEST_COMMAND ""
        INSTALL_COMMAND ""
        LOG_INSTALL ON
        EXCLUDE_FROM_ALL ON
)
ExternalProject_Get_Property(l3pp_ext source_dir)
set(l3pp_INCLUDE "${source_dir}/")
add_imported_library_interface(l3pp_openepl "${l3pp_INCLUDE}")
list(APPEND OPENEPL_DEP_TARGETS l3pp_openepl)
add_dependencies(l3pp_openepl l3pp_ext)
