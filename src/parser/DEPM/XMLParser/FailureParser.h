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
 * @file FailureParser.h
 * @brief This file contains the declaration of the FailureParser class, which is responsible for parsing XML data
 * related to failures in the OpenEPL model.
 */
#pragma once

#include <algorithm>
#include <boost/property_tree/xml_parser.hpp>

#include "Parser.h"

#include "storage/DEPM/Node/Failure.h"
#include "parser/DEPM/NodeDefinitions.h"
#include "storage/DEPM/NodeProps/FailureProps.h"

namespace OpenEPL::parser::DEPM {
    /**
    * @brief The FailureParser class is responsible for parsing XML data related to failures in the OpenEPL DEPM model.
    * @tparam OpenEPL::DEPM::FailureProps The type of the properties of the failure being parsed.
    */
    class FailureParser : public Parser<OpenEPL::DEPM::FailureProps> {
    protected:

        /**
         * @brief Parses the attributes of the failure from the given XML tree.
         * @param props The properties of the failure being parsed.
         * @param xml The XML tree containing the attributes to be parsed.
         */
        void parseAttributes(OpenEPL::DEPM::FailureProps &props, const TreeXML &xml) override {
            parseAttributeName(props, xml);
        }

        /**
         * @brief Parses the value of the failure from the given XML subtree.
         * @param props The properties of the failure being parsed.
         * @param xml The XML subtree containing the value to be parsed.
         */
        void parseValue(OpenEPL::DEPM::FailureProps &props, const SubtreeXML &xml) override {
            auto str = xml.second.data();
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            Parser::parseField(props.property, str);
        }

        /**
         * @brief Parses the sub-trees of the failure from the given XML subtree.
         * @param props The properties of the failure being parsed.
         * @param xml The XML subtree containing the sub-trees to be parsed.
         */
        void parseSubtree(OpenEPL::DEPM::FailureProps &props, const SubtreeXML &xml) override {
            for(const auto &subTree : xml.second) {
                switch(hash(subTree.first.c_str())) {
                    case hash(ATTR_SET):
                        parseAttributes(props, subTree.second);
                        break;
                }
            }
        }

    public:
        /**
         * @brief Constructs a new FailureParser object.
         */
        FailureParser() : Parser(DEPM_XML_TAG_FAILURE) {}
    };
}
