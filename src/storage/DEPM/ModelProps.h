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
#pragma once

#include <set>
#include <ostream>
#include <utility>
#include <boost/property_tree/ptree.hpp>

#include "utility/UnorderedMap.h"
#include "utility/ContainerTypes.h"
#include "storage/DEPM/NodeProps/NodeProps.h"
#include "storage/DEPM/Node/Element.h"
#include "storage/DEPM/Node/Failure.h"
#include "storage/DEPM/Node/Data.h"
#include "storage/DEPM/Arc/ControlFlow.h"
#include "storage/DEPM/Arc/DataFlow.h"

namespace OpenEPL::DEPM {
    /**
     * @brief ModelProps struct holds the properties of a DEPM model.
     */
    struct ModelProps : public NodeProps {
    public:
        std::optional<Key> initialElement; ///< The initial element of the model.

        double step = 0;

        UnorderedMap<Key, Element> elements = {}; ///< The elements in the model.
        UnorderedMap<Key, Failure> failures = {}; ///< The failures in the model.
        UnorderedMap<Key, Data> data = {}; ///< The data in the model.

        std::set<ControlFlow> controlFlows; ///< The control flows in the model.
        std::set<DataFlow> dataFlows; ///< The data flows in the model.

        explicit ModelProps() = default;

        /**
         * @brief Overloads the << operator for outputting the ModelProps.
         * @param os The output stream.
         * @param model The ModelProps object.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const ModelProps &model) {
            const auto initial = model.initialElement.has_value() ? model.initialElement.value() : "none";
            os << "initial element: "<<initial<<std::endl;
            os << "elements ["<<model.elements.size()<<"] ::"<<std::endl;
            for (auto &el: model.elements) os << ": "<<el.first << " :: "<< el.second;
            os << "control_flow ["<<model.controlFlows.size()<<"] ::"<<std::endl;
            for (auto &el: model.controlFlows) os << ": "<<el;
            os << "data_flow ["<<model.dataFlows.size()<<"] ::"<<std::endl;
            for (auto &el: model.dataFlows) os << ": "<<el;
            os << "data ["<<model.data.size()<<"] ::\n";
            for (auto &el: model.data) os << ": "<<el.first << " :: "<< el.second;
            os << "failures ["<<model.failures.size()<<"] ::\n";
            for (auto &el: model.failures) os << ": "<<el.first << " :: "<< el.second;
            return os;
        }
    };
}
