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
 * @file Data.h
 * @brief Contains the declaration of the Data class.
 */

#pragma once
#include <unordered_set>
#include <string>
#include <utility>
#include <ostream>

#include "utility/ContainerTypes.h"
#include "Node.h"
#include "storage/DEPM/NodeProps/DataProps.h"

namespace OpenEPL::DEPM {
    /**
     * @class Data
     * @brief Represents a data node in the DEPM (Data Element Property Model).
     * @tparam DataProps The type of properties associated with the data node.
     */
    class Data : public Node<DataProps> {
        friend class ModelHandler;
        template<class N, class P> friend class NodeTest;

    protected:
        /**
         * @brief Default constructor for the Data class.
         */
        explicit Data(): Node<DataProps>() {};

    public:
        /**
         * @brief Constructor for the Data class.
         * @param props The properties associated with the data node.
         */
        explicit Data(const DataProps &props) : Node<DataProps>(props) {}

        /**
         * @brief Overloaded stream insertion operator for the Data class.
         * @param os The output stream.
         * @param node The data node to be inserted into the stream.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const Data &node) {
            os << node.props;
            return os;
        }

        /**
         * @brief Checks if the initial value is in the set of values.
         * @return True if the initial value is in the set, false otherwise.
         */
        bool isInitialValueInSet() {
            if(props.initial_value.empty() || props.values.empty()) { return false; }
            return props.values.find(props.initial_value) == props.values.end();
        }

        /**
         * @brief Checks if a value is in the set of values.
         * @param value The value to check.
         * @return True if the value is in the set, false otherwise.
         */
        bool isValueInSet(const std::string &value) {
            if(value.empty() || props.values.empty()) { return false; }
            return props.values.find(value) == props.values.end();
        }
    };
}
