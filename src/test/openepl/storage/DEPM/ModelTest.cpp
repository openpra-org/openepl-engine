#include "storage/DEPM/Model.h"
#include "storage/DEPM/Handlers/ModelHandler.h"
#include "test/openepl/storage/DEPM/ModelTest.h"

#include "test/openepl_gtest.h"

TEST(Model, Instantiation) {
    auto model = OpenEPL::DEPM::ModelTest();
}
