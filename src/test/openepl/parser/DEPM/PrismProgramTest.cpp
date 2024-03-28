#include "storage/DEPM/Model.h"
#include "test/openepl_gtest.h"
#include "openepl-config.h"

#include <storm-parsers/parser/PrismParser.h>
#include "api/parser.h"
#include "api/openepl.h"
#include "storm-conv/api/storm-conv.h"

TEST(PrismProgram, GeneratedPrismProgramValidity) {
    storm::prism::Program result;
    EXPECT_NO_THROW(result = storm::parser::PrismParser::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.pm"));
    EXPECT_EQ(storm::prism::Program::ModelType::DTMC, result.getModelType());
    EXPECT_FALSE(result.hasUnboundedVariables());
}

TEST(PrismProgram, GeneratedPrismProgramModuleValidity) {
    storm::prism::Program result;
    result = storm::parser::PrismParser::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.pm");
    EXPECT_EQ(2, result.getNumberOfModules());
    EXPECT_EQ("error_propagation", result.getModule("error_propagation").getName());
    EXPECT_EQ("control_flow", result.getModule("control_flow").getName());
}


TEST(PrismProgram, GeneratedPrismProgramFormulaValidity) {
    storm::prism::Program result;
    result = storm::parser::PrismParser::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.pm");
    const std::set<std::string> expected_formulae = {"Generator_Down", "Failure", "Battery_Low"};

    EXPECT_EQ(3, result.getFormulas().size());
    for(const auto &formula : result.getFormulas()) {
    //EXPECT_TRUE(expected_formulae.contains(formula.getName()));
    }
}

TEST(PrismProgram, GeneratedPrismProgramRewardValidity) {
    storm::prism::Program result;
    result = storm::parser::PrismParser::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.pm");
    const std::set<std::string> expected_rewards = {"time"};

    EXPECT_EQ(1, result.getRewardModels().size());
    for(const auto &reward : result.getRewardModels()) {
    //EXPECT_TRUE(expected_rewards.contains(reward.getName()));
    }
}

TEST(PrismProgram, CheckParsedProgramValidity) {
    /**
     * STEP A.
     */
    //read ErrorPro6 generated prism program from file.
    auto prism_from_file = storm::parser::PrismParser::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.pm");
    //write this file back to disk, call it expected_export
    storm::api::exportPrismToFile(prism_from_file, std::vector<storm::jani::Property>(), OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery_expected.pm");

    /**
     * STEP B.
     */
    //read ErrorPro6 generated depm xml from file.
    auto depm_from_file = *OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery.xml");
    //convert depm xml to prism program
    storm::prism::Program prism_from_depm = *OpenEPL::api::getPrismProgram(depm_from_file);
    //std::vector<storm::jani::Property> properties_from_depm = OpenEPL::api::getJaniProperties(depm_from_file);
    //write asd
    //storm::api::exportPrismToFile(prism_from_depm, properties_from_depm, OPENEPL_TEST_RESOURCES_DIR "/depm/battery/battery_real.pm");
}

TEST(PrismProgram, CheckParsedProgramValidity2) {
    /**
     * STEP A.
     */
    //read ErrorPro6 generated prism program from file.
    auto prism_from_file = storm::parser::PrismParser::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/transmitter/from_errorpro6.pm");
    //write this file back to disk, call it expected_export
    storm::api::exportPrismToFile(prism_from_file, std::vector<storm::jani::Property>(), OPENEPL_TEST_RESOURCES_DIR "/depm/transmitter/from_storm.pm");

    /**
     * STEP B.
     */
    //read ErrorPro6 generated depm xml from file.
    auto depm_from_file = *OpenEPL::api::parse(OPENEPL_TEST_RESOURCES_DIR "/depm/transmitter/transmitter.xml");
    //convert depm xml to prism program
    storm::prism::Program prism_from_depm = *OpenEPL::api::getPrismProgram(depm_from_file);
    //std::vector<storm::jani::Property> properties_from_depm = OpenEPL::api::getJaniProperties(depm_from_file);
    //write asd
    //storm::api::exportPrismToFile(prism_from_depm, properties_from_depm, OPENEPL_TEST_RESOURCES_DIR "/depm/transmitter/from_openepl.pm");
}
