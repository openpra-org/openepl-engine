#ifndef OPENEPL_ENGINE_PARSERTEST_H
#define OPENEPL_ENGINE_PARSERTEST_H

#include "parser/DEPM/XMLParser/Parser.h"

namespace OpenEPL::Test::DEPM {
    template <class NodeTypeProps> class ParserTest : public parser::DEPM::Parser<NodeTypeProps> {
    public:
        void parseValue(NodeTypeProps &props, const parser::SubtreeXML &xml) override {

        }

        void parseSubtree(NodeTypeProps &props, const parser::SubtreeXML &xml) override {

        }

        void parseAttributes(NodeTypeProps &props, const parser::TreeXML &xml) override {

        }

        explicit ParserTest(const parser::Key &tag) : parser::DEPM::Parser<NodeTypeProps>(tag) {}
        static constexpr unsigned int hash(const char *s, int off = 0) {
            return parser::DEPM::Parser<NodeTypeProps>::hash(s, off);
        }

        template <class N, class P> static void insert(OpenEPL::DEPM::UnorderedMap<parser::Key, N> &map, const P &props) {
           parser::DEPM::Parser<NodeTypeProps>::insert(map, props);
        }

        template <class N, class P> static void insert(OpenEPL::DEPM::Set<N> &set, const P &props) {
            parser::DEPM::Parser<NodeTypeProps>::insert(set, props);
        }

        template <typename Prop, typename Src> static void parseField(Prop &prop, const Src &xml) {
            prop = xml;
        }

        template <class NP> static void parseAttributeName(NP &props, const parser::TreeXML &xml) {
            parser::DEPM::Parser<NodeTypeProps>::parseAttributeName(props, xml);
        }
    };
}

#endif //OPENEPL_ENGINE_PARSERTEST_H
