#include "test/openepl_gtest.h"
#include "openepl-config.h"

#include "storage/DEPM/Model.h"
#include "api/parser.h"
#include "parser/DEPM/XMLParser/ModelParser.h"

namespace OpenEPL::Test::DEPM {
    class ModelParserTest : public OpenEPL::parser::DEPM::ModelParser {
    public:

    };
}

TEST(ModelParserTest, ParseNotNull) {
auto model_ptr = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml");
EXPECT_NE(model_ptr, nullptr);
}

TEST(ModelParserTest, ParseDEPModelBattery) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml");
    std::cout<<model<<std::endl;
}

TEST(ModelParserTest, ParseDEPModelBatteryRecovery) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery_recovery.xml");
    std::cout<<model<<std::endl;
}

TEST(ModelParserTest, ParseDEPModelTwoBatteries) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/two_batteries.xml");
    std::cout<<model<<std::endl;
}

TEST(ModelParserTest, ParseDEPModelABC) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/abc/abc.xml");
    std::cout<<model<<std::endl;
}
