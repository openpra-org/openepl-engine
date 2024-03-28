set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SRC
        handler.h
        openepl.h
        parser.h
        parser.cpp
        quantifier.h
        quantifier.cpp
        transformer.h
        transformer.cpp
)

add_library(api ${LIB_SRC})
set_target_properties(api PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(api transformer parser storage utility storm)
#l3pp_openepl
#target_link_libraries(lib_inlab1 utils ${Boost_PROGRAM_OPTIONS_LIBRARY})
