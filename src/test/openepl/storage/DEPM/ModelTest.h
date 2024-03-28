#pragma once

#include "storage/DEPM/Model.h"

namespace OpenEPL::DEPM {
    class ModelTest : public Model {
    public:
        explicit ModelTest(const ModelProps &props) : Model(props) {}
        explicit ModelTest() : Model() {}
    };
}
