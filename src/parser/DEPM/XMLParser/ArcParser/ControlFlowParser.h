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
 * @file ControlFlowParser.h
 * @brief This file contains the declaration of the ControlFlowParser class, which is responsible for parsing XML data
 * related to control flow in the OpenEPL model.
 */
#pragma once

#include <boost/property_tree/xml_parser.hpp>

#include "storage/DEPM/Arc/ControlFlow.h"
#include "parser/DEPM/NodeDefinitions.h"
#include "parser/DEPM/XMLParser/Parser.h"

namespace OpenEPL::parser::DEPM {
    /**
    * @brief The ControlFlowParser class is responsible for parsing XML data related to control flow in the OpenEPL DEPM model.
    * @tparam OpenEPL::DEPM::ControlFlowProps The type of the properties of the control flow being parsed.
    */
    class ControlFlowParser : public Parser<OpenEPL::DEPM::ControlFlowProps> {
    public:
        /**
         * @brief Constructs a new ControlFlowParser object.
         */
        ControlFlowParser() : Parser(DEPM_XML_TAG_CONTROL_FLOW) {}

    protected:
        /**
         * @brief Parses the value of the control flow from the given XML subtree.
         * @param props The properties of the control flow being parsed.
         * @param xml The XML subtree containing the value to be parsed.
         */
        void parseValue(OpenEPL::DEPM::ControlFlowProps &props, const SubtreeXML &xml) override {

        }

        /**
         * @brief Parses the sub-trees of the control flow from the given XML subtree.
         * @param props The properties of the control flow being parsed.
         * @param xml The XML subtree containing the sub-trees to be parsed.
         */
        void parseSubtree(OpenEPL::DEPM::ControlFlowProps &props, const SubtreeXML &xml) override {
            for(const auto &subTree : xml.second) {
                switch(hash(subTree.first.c_str())) {
                    case hash(ATTR_SET):
                        parseAttributes(props, subTree.second);
                        break;
                }
            }
        }

        /**
         * @brief Parses the attributes of the control flow from the given XML tree.
         * @param props The properties of the control flow being parsed.
         * @param xml The XML tree containing the attributes to be parsed.
         */
        void parseAttributes(OpenEPL::DEPM::ControlFlowProps &props, const TreeXML &xml) override {
            auto to = xml.get_child(DEPM_XML_ATTR_TO, EMPTY_TREE).data();
            to.erase(std::remove(to.begin(), to.end(), ' '), to.end());
            parseField(props.sink, to);

            auto from = xml.get_child(DEPM_XML_ATTR_FROM, EMPTY_TREE).data();
            from.erase(std::remove(from.begin(), from.end(), ' '), from.end());
            parseField(props.source, from);
        }
    };
}
