#include "storage/DEPM/Node/Node.h"

#include "test/openepl_gtest.h"

using namespace OpenEPL::DEPM;

TEST(NodeProps, Instantiation) {
    auto nodeProps1 = NodeProps();
    nodeProps1.name = "aNode";
    EXPECT_EQ(nodeProps1.name, "aNode");

    auto nodeProps2 = NodeProps("bNode");
    EXPECT_EQ(nodeProps2.name, "bNode");
}

TEST(NodeProps, AssignmentOperator) {
    auto nodeProps1 = NodeProps();
    nodeProps1.name = "aNode";

    auto nodeProps2 = nodeProps1;
    EXPECT_NE(&nodeProps1, &nodeProps2); // assignment is copy-construction, so different variables
    EXPECT_EQ(nodeProps1.name, nodeProps2.name);
}

TEST(NodeProps, CopyConstructor) {
    NodeProps nodeProps1 = NodeProps();
    nodeProps1.name = "aNode";

    NodeProps nodeProps2 = NodeProps(nodeProps1);
    EXPECT_NE(&nodeProps1, &nodeProps2);
    EXPECT_EQ(nodeProps1.name, nodeProps2.name);
}

TEST(NodeProps, Populate) {
    NodeProps nodeProps1 = NodeProps();
    nodeProps1.name = "aNode";

    NodeProps nodeProps2 = NodeProps();
    nodeProps2.name = nodeProps1.name;

    EXPECT_NE(&nodeProps1, &nodeProps2);
    EXPECT_EQ(nodeProps1.name, nodeProps2.name);
}
