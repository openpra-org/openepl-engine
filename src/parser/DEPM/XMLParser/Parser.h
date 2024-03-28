/*
    Copyright (C) 2023 OpenPRA Initiative

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/**

@file Parser.h
@brief This file contains the declaration of the abstract Parser class, which is responsible for parsing XML data
*/
#pragma once

#include <algorithm>

#include "utility/ContainerTypes.h"
#include "utility/ParserTypes.h"
#include "parser/DEPM/NodeDefinitions.h"

#include <utility>

/**
 * @namespace OpenEPL::parser::DEPM
 * @brief Namespace for the DEPM parser.
 */
namespace OpenEPL::parser::DEPM {

    /**
     * @brief Builds an empty property tree.
     * @return A reference to the empty property tree.
     */
    const static PropertyTree &BuildEmptyTree() {
        static PropertyTree t;
        return t;
    }
    const static auto EMPTY_TREE = BuildEmptyTree();

    /**
     * @class Parser
     * @brief A base class for parsing DEPM nodes.
     * @tparam NodeTypeProps The properties of the node type.
     */
    template <class NodeTypeProps> class Parser {
        friend class ParserTest;

    protected:
        const Key TAG; ///< The tag of the node type.

        /**
         * @brief Parses the value of the node.
         * @param props The properties of the node.
         * @param xml The XML subtree.
         */
        virtual void parseValue(NodeTypeProps &props, const SubtreeXML &xml) = 0;

        /**
         * @brief Parses the subtree of the node.
         * @param props The properties of the node.
         * @param xml The XML subtree.
         */
        virtual void parseSubtree(NodeTypeProps &props, const SubtreeXML &xml) = 0;

        /**
         * @brief Parses the attributes of the node.
         * @param props The properties of the node.
         * @param xml The XML tree.
         */
        virtual void parseAttributes(NodeTypeProps &props, const TreeXML &xml) = 0;

        /**
         * @brief Computes the hash of a string.
         * @param s The string to hash.
         * @param off The offset to start hashing from.
         * @return The computed hash.
         */
        static constexpr unsigned int hash(const char *s, int off = 0) {
            return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];
        }

        /**
         * @brief Inserts a node into a map.
         * @tparam N The node type.
         * @tparam P The properties type.
         * @param map The map to insert the node into.
         * @param props The properties of the node.
         */
        template <class N, class P> static void insert(OpenEPL::DEPM::UnorderedMap<Key, N> &map, const P &props) {
            map.insert_or_assign(props.name, N(props));
        }

        /**
         * @brief Inserts a node into a set.
         * @tparam N The node type.
         * @tparam P The properties type.
         * @param set The set to insert the node into.
         * @param props The properties of the node.
         */
        template <class N, class P> static void insert(OpenEPL::DEPM::Set<N> &set, const P &props) {
            set.insert(N(props));
        }

        /**
         * @brief Parses a field from the XML source.
         * @tparam Prop The property type.
         * @tparam Src The XML source type.
         * @param prop The property to parse.
         * @param xml The XML source.
         */
        template <typename Prop, typename Src> static void parseField(Prop &prop, const Src &xml) {
            prop = xml;
        }

        /**
         * @brief Parses the name attribute of a node.
         * @tparam NP The node properties type.
         * @param props The properties of the node.
         * @param xml The XML tree.
         */
        template <class NP> static void parseAttributeName(NP &props, const TreeXML &xml) {
            auto str = xml.get_child(DEPM_XML_ATTR_NAME, EMPTY_TREE).data();
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            parseField(props.name, str);
        }

    public:
        /**
         * @brief Constructs a parser with the given tag.
         * @param tag The tag of the node type.
         */
        explicit Parser(Key tag): TAG(std::move(tag)) {}

        /**
         * @brief Parses a node from the XML subtree.
         * @param xml The XML subtree.
         * @return The properties of the parsed node.
         */
        NodeTypeProps parse(const SubtreeXML& xml) {
            NodeTypeProps props = NodeTypeProps();
            parseValue(props, xml);
            parseSubtree(props, xml);
            return props;
        };

    };
}
