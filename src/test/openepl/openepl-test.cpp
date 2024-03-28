#include <storm/settings/SettingsManager.h>
#include "test/openepl_gtest.h"

int main(int argc, char **argv) {
    storm::settings::initializeAll("OpenEPL (Functional) Testing Suite", "test");
    storm::test::initialize();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
