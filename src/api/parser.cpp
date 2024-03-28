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
#include <boost/property_tree/xml_parser.hpp>

#include "parser.h"
#include "parser/DEPM/XMLParser/ModelParser.h"
#include "storage/DEPM/Handlers/ModelHandler.h"
#include "parser/DEPM/NodeDefinitions.h"

namespace OpenEPL::api {

    std::shared_ptr<OpenEPL::DEPM::Model> parse(std::string const& filename) {
        boost::property_tree::ptree xml;
        boost::property_tree::read_xml(filename, xml);
        for (auto &modelTreeXML: xml.get_child(DEPM_XML_TAG_OPENEPL, parser::DEPM::EMPTY_TREE)) {
            auto modelProps = parser::DEPM::ModelParser().parse(modelTreeXML);
            auto model_ptr = std::make_shared<OpenEPL::DEPM::Model>(modelProps);
            return model_ptr;
        }
        return nullptr;
    }
}
