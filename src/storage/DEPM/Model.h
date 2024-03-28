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

#include "ModelProps.h"

namespace OpenEPL::DEPM {
    /**
     * @brief The Model class represents a DEPM model.
     */
    class Model : public Node<ModelProps> {
        friend class ModelHandler;
        friend class ModelTest;
        friend class ModelTransformerTest;

    public:
        /**
         * @brief Constructs a new Model object with the given properties.
         * @param props The properties of the model.
         */
        explicit Model(const ModelProps &props) : Node<ModelProps>(props) {}

        /**
         * @brief Constructs a new Model object with default properties.
         */
        explicit Model() : Node<ModelProps>() {}

        template<class FLOW_TYPE> static std::pair<std::set<FLOW_TYPE>, std::set<FLOW_TYPE>> getFlows(const Key &name, const std::set<FLOW_TYPE> &flows) {
            auto sourceFlows = std::set<FLOW_TYPE>();
            auto sinkFlows = std::set<FLOW_TYPE>();
            for(const auto &flow : flows) {
                const auto &props = flow.getProperties();
                if (props.source == name) {
                    sourceFlows.insert(flow);
                }
                if (props.sink == name) {
                    sinkFlows.insert(flow);
                }
            }
            return std::pair(sourceFlows, sinkFlows);
        }

        std::set<ControlFlow> getControlFlowsForSource(const Key &node) const {
            return Model::getFlows(node, getProperties().controlFlows).first;
        }

        std::set<DataFlow> getDataFlowsForSource(const Key &node) const {
            return Model::getFlows(node, getProperties().dataFlows).first;
        }

        std::pair<std::set<DataFlow>, std::set<DataFlow>> getDataFlows(const Key &node) const {
            return Model::getFlows(node, getProperties().dataFlows);
        }

        std::pair<std::set<ControlFlow>, std::set<ControlFlow>> getControlFlows(const Key &node) const {
            return Model::getFlows(node, getProperties().controlFlows);
        }

        std::set<ControlFlow> getControlFlowsForSink(const Key &node) const {
            return Model::getFlows(node, getProperties().controlFlows).second;
        }

        std::set<DataFlow> getDataFlowsForSink(const Key &node) const {
            return Model::getFlows(node, getProperties().dataFlows).second;
        }
    };
}
