#include "storage/DEPM/Model.h"
#include "test/openepl_gtest.h"
#include "openepl-config.h"

#include "api/parser.h"

TEST(ParserAPI, ParseDEPModelBattery) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml");
    std::cout<<*model<<std::endl;
}

TEST(ParserAPI, ParseDEPModelBatteryRecovery) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery_recovery.xml");
    std::cout<<*model<<std::endl;
}

TEST(ParserAPI, ParseDEPModelTwoBatteries) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/two_batteries.xml");
    std::cout<<*model<<std::endl;
}

TEST(ParserAPI, ParseDEPModelABC) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/abc/abc.xml");
    std::cout<<*model<<std::endl;
}

TEST(ParserAPI, TransmitterXML) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/transmitter/transmitter.xml");
    std::cout<<*model<<std::endl;
}

TEST(ParserAPI, MobileRobotXML) {
    auto model = OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/mobile_robot/mobile_robot.xml");
    std::cout<<*model<<std::endl;
}
