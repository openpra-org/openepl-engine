#ifndef OPENEPL_ENGINE_NODETEST_H
#define OPENEPL_ENGINE_NODETEST_H

namespace OpenEPL::DEPM {
    template <class NodeType, class PropsType> class NodeTest {
    public:
        NodeType node;
        explicit NodeTest() : node(NodeType()) {}
        explicit NodeTest(PropsType &props) : node(NodeType(props)) {}
        explicit NodeTest(NodeType &node) : node(NodeType(node)) {}
        [[nodiscard]] PropsType &getProperties() { return node.props; }
        void setProperties(const PropsType &propsToSet) { node.props = propsToSet; }
    };
}

namespace OpenEPL::DEPM {
    template <class PropsType> class PropsTest {
    public:
        PropsType &props;
        explicit PropsTest() : props(PropsType()) {}
        explicit PropsTest(PropsType &props) : props(props) {}
    };
}


#endif //OPENEPL_ENGINE_NODETEST_H
