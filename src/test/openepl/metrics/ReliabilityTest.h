#pragma once

#include "test/openepl_gtest.h"
#include "metrics/Reliability.h"

TEST(Reliability, Constructor) {
    //auto metrics = OpenEPL::Metrics::DEPM::Reliability<double, double>();
    //EXPECT_NO_THROW(metrics);
}

TEST(Reliability, Constructor2) {
    auto x = 3 + 5;
    EXPECT_TRUE(x == 8);
}
