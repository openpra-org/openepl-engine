set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SRC
        ContainerTypes.h
        Helpers.h
        ParserTypes.h
        UnorderedMap.h
)

add_library(utility ${LIB_SRC})
set_target_properties(utility PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(lib_inlab1 utils ${Boost_PROGRAM_OPTIONS_LIBRARY})
