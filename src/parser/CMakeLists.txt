set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SRC
        DEPM/NodeDefinitions.h
        DEPM/XMLParser/CFCParser.h
        DEPM/XMLParser/DataParser.h
        DEPM/XMLParser/ElementParser.h
        DEPM/XMLParser/EPCParser.h
        DEPM/XMLParser/FailureParser.h
        DEPM/XMLParser/ModelParser.h
        DEPM/XMLParser/Parser.h
        DEPM/XMLParser/ArcParser/DataFlowParser.h
        DEPM/XMLParser/ArcParser/ControlFlowParser.h
)

add_library(parser ${LIB_SRC})
set_target_properties(parser PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(lib_inlab1 utils ${Boost_PROGRAM_OPTIONS_LIBRARY})
