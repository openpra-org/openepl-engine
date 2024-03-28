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
 * @file ModelParser.h
 * @brief This file contains the declaration of the ModelParser class, which is responsible for parsing XML data
*/

#pragma once

#include <boost/property_tree/xml_parser.hpp>

#include "storage/DEPM/Model.h"
#include "storage/DEPM/Node/Node.h"
#include "parser/DEPM/NodeDefinitions.h"
#include "Parser.h"

#include "DataParser.h"
#include "ElementParser.h"
#include "FailureParser.h"

#include "parser/DEPM/XMLParser/ArcParser/DataFlowParser.h"
#include "parser/DEPM/XMLParser/ArcParser/ControlFlowParser.h"

namespace OpenEPL::parser::DEPM {

    /**
     * @class ModelParser
     * @brief This class is responsible for parsing XML data related to a DEPM model.
     */
    class ModelParser : public Parser<OpenEPL::DEPM::ModelProps> {
        friend class ModelParserTest;
    private:
    protected:

        /**
         * @brief Parses the value of the XML subtree.
         * @param props The properties of the DEPM model.
         * @param xml The XML subtree to be parsed.
         */
        void parseValue(OpenEPL::DEPM::ModelProps &props, const SubtreeXML &xml) override {

        }

        /**
         * @brief Parses the XML subtree.
         * @param props The properties of the DEPM model.
         * @param xml The XML subtree to be parsed.
         */
        void parseSubtree(OpenEPL::DEPM::ModelProps &props, const SubtreeXML &xml) override {
            for (const auto &tree: xml.second) {
                switch(hash(tree.first.c_str())) {
                    case hash(ATTR_SET):
                        parseAttributes(props, tree.second);
                        break;

                    case hash(DEPM_XML_TAG_ELEMENT):
                        Parser::insert(props.elements, ElementParser().parse(tree));
                        break;

                    case hash(DEPM_XML_TAG_DATA):
                        Parser::insert(props.data, DataParser().parse(tree));
                        break;

                    case hash(DEPM_XML_TAG_FAILURE):
                        Parser::insert(props.failures, FailureParser().parse(tree));
                        break;

                    case hash(DEPM_XML_TAG_CONTROL_FLOW):
                        Parser::insert(props.controlFlows, ControlFlowParser().parse(tree));
                        break;

                    case hash(DEPM_XML_TAG_DATA_FLOW):
                        Parser::insert(props.dataFlows, DataFlowParser().parse(tree));
                        break;

                    default:
                        std::cerr<<"Unable to parse key in model:: "<<tree.first<<"\n";
                }
            }
        }

        /**
         * @brief Parses the attributes of the XML subtree.
         * @param props The properties of the DEPM model.
         * @param xml The XML subtree to be parsed.
         */
        void parseAttributes(OpenEPL::DEPM::ModelProps &props, const TreeXML &xml) override {
            parseAttributeName(props, xml);
            parseField(props.initialElement, xml.get_child(DEPM_XML_ATTR_INITIAL_ELEMENT, EMPTY_TREE).data());
        }

    public:

        /**
         * @brief Constructor for the ModelParser class.
         */
        ModelParser(): Parser(DEPM_XML_TAG_MODEL) {}
    };
}
