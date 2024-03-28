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
 * @file ElementParser.h
 * @brief This file contains the declaration of the ElementParser class, which is responsible for parsing XML data
 * related to elements in the OpenEPL model.
 */
#pragma once

#include <boost/property_tree/xml_parser.hpp>

#include "storage/DEPM/Node/Element.h"
#include "parser/DEPM/NodeDefinitions.h"
#include "Parser.h"
#include "EPCParser.h"
#include "CFCParser.h"
#include "storage/DEPM/NodeProps/ElementProps.h"

namespace OpenEPL::parser::DEPM {
    /**
    * @brief The ElementParser class is responsible for parsing XML data related to elements in the OpenEPL DEPM model.
    * @tparam OpenEPL::DEPM::ElementProps The type of the properties of the element being parsed.
    */
    class ElementParser : public Parser<OpenEPL::DEPM::ElementProps> {
    public:
    protected:
        /**
         * @brief Parses the value of the element from the given XML subtree.
         * @param props The properties of the element being parsed.
         * @param xml The XML subtree containing the value to be parsed.
         */
        void parseValue(OpenEPL::DEPM::ElementProps &props, const SubtreeXML &xml) override {

        }

        /**
         * @brief Parses the sub-trees of the element from the given XML subtree.
         * @param props The properties of the element being parsed.
         * @param xml The XML subtree containing the sub-trees to be parsed.
         */
        void parseSubtree(OpenEPL::DEPM::ElementProps &props, const SubtreeXML &xml) override {
            for(const auto &subTree : xml.second) {
                switch(hash(subTree.first.c_str())) {
                    case hash(ATTR_SET):
                        parseAttributes(props, subTree.second);
                        break;
                    case hash(DEPM_XML_TAG_EPC):
                        Parser::insert(props.epcs, EPCParser().parse(subTree));
                        break;
                    case hash(DEPM_XML_TAG_CFC):
                        Parser::insert(props.cfcs, CFCParser().parse(subTree));
                        break;
                }
            }
        }

        /**
         * @brief Parses the attributes of the element from the given XML tree.
         * @param props The properties of the element being parsed.
         * @param xml The XML tree containing the attributes to be parsed.
         */
        void parseAttributes(OpenEPL::DEPM::ElementProps &props, const TreeXML &xml) override {
            parseAttributeName(props, xml);
            parseAttributeTime(props, xml);
            parseAttributeInitial(props, xml);
        }

        /**
         * @brief Parses the "time" attribute of the element from the given XML tree.
         * @param props The properties of the element being parsed.
         * @param xml The XML tree containing the "time" attribute to be parsed.
         */
        static void parseAttributeTime(OpenEPL::DEPM::ElementProps &props, const TreeXML &xml) {
            const auto timeStr = xml.get_child(DEPM_XML_ATTR_TIME, EMPTY_TREE).data();
            double parsedValue;
            try {
                parsedValue = std::stod(timeStr);
            } catch(std::exception &e) {
                parsedValue = 1.0;
            }
            parseField(props.time, parsedValue);
        }

        /**
         * @brief Parses the "initial" attribute of the element from the given XML tree.
         * @param props The properties of the element being parsed.
         * @param xml The XML tree containing the "initial" attribute to be parsed.
         */
        static void parseAttributeInitial(OpenEPL::DEPM::ElementProps &props, const TreeXML &xml) {
            std::istringstream(xml.get_child(DEPM_XML_ATTR_INITIAL, EMPTY_TREE).data()) >> props.initial;
        }

    public:
        /**
         * @brief Constructs a new ElementParser object.
         */
        ElementParser() : Parser(DEPM_XML_TAG_ELEMENT) {}
    };
}
