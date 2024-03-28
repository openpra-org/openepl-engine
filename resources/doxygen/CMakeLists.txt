# Enable operator IN_LIST to avoid problems with CMake version 3.12
if(POLICY CMP0057)
    cmake_policy(SET CMP0057 NEW)
endif()

find_package(Doxygen
             REQUIRED doxygen dot)
# Add a target to generate API documentation with Doxygen
if(DOXYGEN_FOUND)
        # We use the doxygen command of CMake instead of using the separate config file
        set(DOXYGEN_PROJECT_NAME "OpenEPL")
        set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
        set(DOXYGEN_CASE_SENSE_NAMES NO)
        set(DOXYGEN_PROJECT_BRIEF "C++ implementation of DEPM")
        set(DOXYGEN_BRIEF_MEMBER_DESC YES)
        set(DOXYGEN_REPEAT_BRIEF YES)
        set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
        set(DOXYGEN_QT_AUTOBRIEF YES)
        set(DOXYGEN_EXTRACT_ALL YES)
        set(DOXYGEN_EXTRACT_STATIC YES)
        set(DOXYGEN_SOURCE_BROWSER YES)
        set(DOXYGEN_GENERATE_TREEVIEW YES)
        set(DOXYGEN_CASE_SENSE_NAMES NO)
        set(DOXYGEN_HTML_TIMESTAMP YES)
        set(DOXYGEN_CREATE_SUBDIRS YES)
        set(DOXYGEN_GENERATE_LATEX YES)
        set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc")
        doxygen_add_docs(
            doc
            "${PROJECT_SOURCE_DIR}/src/api"
            COMMENT "Generating API documentation with Doxygen"
        )

        add_custom_target(doxygen_pdf
                COMMENT "Generating Doxygen Manual PDF."
                COMMAND make
                DEPENDS doc
                WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/latex"
        )
endif(DOXYGEN_FOUND)
