#include "test/openepl/storage/DEPM/Node/NodeTest.h"
#include "storage/DEPM/Node/Node.h"
#include "test/openepl_gtest.h"

using namespace OpenEPL::DEPM;
TEST(Node, Instantiation) {
    NodeTest<Node<NodeProps>, NodeProps>();
}

TEST(Node, AssignmentOperator) {
    auto testNode1 = NodeTest<Node<NodeProps>, NodeProps>();
    NodeTest<Node<NodeProps>, NodeProps> testNode2;
    EXPECT_NO_THROW(testNode2 = testNode1);
    EXPECT_FALSE(testNode1.node == testNode2.node); // two separate objects with same value
}

TEST(Node, ReferenceAssignmentOperator) {
    auto testNode1 = NodeTest<Node<NodeProps>, NodeProps>();
    NodeTest<Node<NodeProps>, NodeProps> &testNode2 = testNode1;
    EXPECT_TRUE(testNode1.node == testNode2.node); // identical object
}

TEST(Node, ComparisonOperator) {
    auto testNode1 = NodeTest<Node<NodeProps>, NodeProps>();
    auto testNode2 = NodeTest<Node<NodeProps>, NodeProps>();
    if (std::addressof(testNode1.node) < std::addressof(testNode2.node)) {
        EXPECT_LT(testNode1.node, testNode2.node);
    } else {
        EXPECT_GT(testNode1.node, testNode2.node);
    }
}

TEST(Node, CopyConstructor) {
    auto testNode1 = NodeTest<Node<NodeProps>, NodeProps>();
    auto testNode2 = OpenEPL::DEPM::NodeTest(testNode1);
    EXPECT_FALSE(testNode1.node == testNode2.node); // two separate objects with same value
}
