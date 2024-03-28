set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SRC
        DEPM/ModelDefinitions.h
        DEPM/ModelTransformer.h
        DEPM/ModelTransformer.cpp
)

add_library(transformer ${LIB_SRC})
set_target_properties(transformer PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(transformer storm)
#target_link_libraries(lib_inlab1 utils ${Boost_PROGRAM_OPTIONS_LIBRARY})
