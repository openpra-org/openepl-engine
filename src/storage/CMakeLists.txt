set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SRC
        DEPM/Arc/Arc.h
        DEPM/Arc/ControlFlow.h
        DEPM/Arc/DataFlow.h
        DEPM/Handlers/MapHandler.h
        DEPM/Handlers/ModelHandler.h
        DEPM/Handlers/ModelHandler.cpp
        DEPM/Node/CFC.h
        DEPM/Node/Data.h
        DEPM/Node/Element.h
        DEPM/Node/EPC.h
        DEPM/Node/Failure.h
        DEPM/Node/Node.h
        DEPM/NodeProps/CFCProps.h
        DEPM/NodeProps/DataProps.h
        DEPM/NodeProps/ElementProps.h
        DEPM/NodeProps/EPCProps.h
        DEPM/NodeProps/PropsType.h
        DEPM/Model.h
        DEPM/ModelProps.h
)

add_library(storage ${LIB_SRC})
set_target_properties(storage PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(storage api storm)
#target_link_libraries(lib_inlab1 utils ${Boost_PROGRAM_OPTIONS_LIBRARY})
