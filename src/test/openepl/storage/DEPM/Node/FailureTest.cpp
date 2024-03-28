#include "storage/DEPM/Node/Failure.h"
#include "test/openepl/storage/DEPM/Node/NodeTest.h"
#include "test/openepl_gtest.h"


using namespace OpenEPL::DEPM;
TEST(Failure, Constructor) {
    auto failure1 = NodeTest<Failure, FailureProps>();
}

TEST(Failure, Populate) {
    auto props = FailureProps("CONDITION x >= 5.39");
    auto failure = NodeTest<Failure, FailureProps>(props);
    EXPECT_EQ("CONDITION x >= 5.39", failure.getProperties().property);
}

TEST(Failure, CopyConstructor) {

}


TEST(Failure, CopyAssignmentOperator) {
    auto props1 = FailureProps("CONDITION x >= 5.39");
    auto failure1 = NodeTest<Failure, FailureProps>(props1);
    auto failure2 = failure1;

    auto props2 = FailureProps("value");
    failure2.setProperties(props2);
    EXPECT_EQ("value", failure2.getProperties().property);
    EXPECT_EQ("CONDITION x >= 5.39", failure1.getProperties().property);
}

TEST(Failure, EqualityOperator) {
    auto props1 = FailureProps("CONDITION x >= 5.39");
    auto failure1 = NodeTest<Failure, FailureProps>(props1);
    auto failure2 = NodeTest<Failure, FailureProps>(props1);
    EXPECT_TRUE(failure1.node != failure2.node); // different objects, same value

    auto props2 = FailureProps("CONDITION x < 9.30");
    auto failure3 = NodeTest<Failure, FailureProps>(props2);
    EXPECT_FALSE(failure1.node == failure3.node); // different objects, different values
}

TEST(Failure, ComparisonOperator) {

}
