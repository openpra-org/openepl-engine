#include "storage/DEPM/Model.h"
#include "test/openepl_gtest.h"
#include "openepl-config.h"

#include "api/openepl.h"

#include <chrono>

TEST(QuantifierAPI, DEPModelBattery) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml", "P=? [ F TransmissionFault]");
    std::cout<<results<<std::endl;
}

TEST(QuantifierAPI, MTTF_GeneratorDown) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml", "R{\"time\"}=? [ F Generator_Down]");
    std::cout<<results<<std::endl;
}

TEST(QuantifierAPI, MTTF_BatteryLow) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml", "R{\"time\"}=? [ F Battery_Low]");
    std::cout<<"Battery_Low: "<<results<<std::endl;
}

TEST(QuantifierAPI, MTTF_BatteryLow_API) {
    auto results = OpenEPL::api::time::mttf(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml", "Battery_Low");
    std::cout<<"Battery_Low: "<<results<<std::endl;
}

TEST(QuantifierAPI, P_BatteryLow_API) {
    auto results = OpenEPL::api::probability::steadystate(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml", "Battery_Low");
    std::cout<<"Battery_Low: "<<results<<std::endl;
}


TEST(QuantifierAPI, P_BatteryLow) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml", "P=? [ F Battery_Low]");
    std::cout<<"P(Battery_Low): "<<results<<std::endl;
}

TEST(QuantifierAPI, P_Failure) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/mobile_robot/mobile_robot.xml", "P=? [ F Failure]");
    std::cout<<"P(Failure): "<<results<<std::endl;
}

TEST(QuantifierAPI, P_ErrorState) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/mobile_robot/mobile_robot.xml", "P=? [ F ErrorState]");
    std::cout<<"P(Failure): "<<results<<std::endl;
}

TEST(QuantifierAPI, MTTF_FailStop) {
    auto results = OpenEPL::api::checkProperty(OPENEPL_TEST_RESOURCES_DIR "/depm/mobile_robot/mobile_robot.xml", "R{\"time\"}=? [ F FailStop]");
    std::cout<<"P(Failure): "<<results<<std::endl;
}

TEST(QuantifierAPI, SteadyStateProbability_FailStop) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    double avg = 0;
    for(auto i=0; i<100; i++) {
        auto t1 = high_resolution_clock::now();
        auto results = OpenEPL::api::probability::steadystate(OPENEPL_TEST_RESOURCES_DIR "/depm/mobile_robot/mobile_robot.xml", "FailStop");
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        avg += ms_double.count();
    }
}

TEST(QuantifierAPI, MTTF_API) {
    auto results = OpenEPL::api::time::mttf(OPENEPL_TEST_RESOURCES_DIR "/depm/mobile_robot/mobile_robot.xml", "FailStop");
    std::cout<<"MTTF(FailStop): "<<results<<std::endl;
}
