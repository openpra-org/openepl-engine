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
 * @file DataParser.h
 * @brief This file contains the declaration of the DataParser class, which is responsible for parsing XML data
 * related to data in the OpenEPL model.
 */
#pragma once

#include <algorithm>
#include <boost/property_tree/xml_parser.hpp>

#include "Parser.h"
#include "storage/DEPM/Node/Data.h"
#include "parser/DEPM/NodeDefinitions.h"
#include "storage/DEPM/NodeProps/DataProps.h"

namespace OpenEPL::parser::DEPM {
    /**
    * @brief The DataParser class is responsible for parsing XML data related to data in the OpenEPL DEPM model.
    * @tparam OpenEPL::DEPM::DataProps The type of the properties of the data being parsed.
    */
    class DataParser : public Parser<OpenEPL::DEPM::DataProps> {
    public:
        /**
         * @brief Constructs a new DataParser object.
         */
        DataParser() : Parser(DEPM_XML_TAG_DATA) {}

    protected:
        /**
         * @brief Parses the value of the data from the given XML subtree.
         * @param props The properties of the data being parsed.
         * @param xml The XML subtree containing the value to be parsed.
         */
        void parseValue(OpenEPL::DEPM::DataProps &props, const SubtreeXML &xml) override {

        }

        /**
         * @brief Parses the sub-trees of the data from the given XML subtree.
         * @param props The properties of the data being parsed.
         * @param xml The XML subtree containing the sub-trees to be parsed.
         */
        void parseSubtree(OpenEPL::DEPM::DataProps &props, const SubtreeXML &xml) override {
            for(const auto &subTree : xml.second) {
                switch(hash(subTree.first.c_str())) {
                    case hash(ATTR_SET):
                        parseAttributes(props, subTree.second);
                        break;
                }
            }
        }

        /**
         * @brief Parses the attributes of the data from the given XML tree.
         * @param props The properties of the data being parsed.
         * @param xml The XML tree containing the attributes to be parsed.
         */
        void parseAttributes(OpenEPL::DEPM::DataProps &props, const TreeXML &xml) override {
            parseAttributeName(props, xml);
            auto str = xml.get_child(DEPM_XML_ATTR_VALUES, EMPTY_TREE).data();
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            const auto wasEmpty = str.empty();
            if(wasEmpty) {
                str += "ok,error";
            }
            OpenEPL::DEPM::NodeProps::tokenize(str, props.values);
            props.initial_value = xml.get_child(DEPM_XML_ATTR_INITIAL_VALUE, EMPTY_TREE).data();
            if(props.initial_value.empty()) {
                props.initial_value = wasEmpty ? "ok" : *props.values.begin();
            }
        }
    };
}
