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
#include <unordered_set>
#include <string>
#include <utility>
#include <ostream>

#include "utility/ContainerTypes.h"
#include "NodeProps.h"

namespace OpenEPL::DEPM {

    /**
     * @brief A struct that represents the properties of a data node.
     * Inherits from NodeProps.
     */
    struct DataProps : public NodeProps {
    public:
        UnorderedSet<Key> values = UnorderedSet<Key>(); /**< The set of values associated with the data node. */
        Key initial_value; /**< The initial value of the data node. */

        /**
         * @brief Default constructor.
         */
        explicit DataProps() = default;

        /**
         * @brief Constructor that sets the values of the data node.
         * @param toSet The set of values to be set.
         */
        explicit DataProps(const UnorderedSet<Key> &toSet): values(toSet) {}

        /**
         * @brief Constructor that sets the values and initial value of the data node.
         * @param toSet The set of values to be set.
         * @param initial The initial value to be set.
         */
        explicit DataProps(const UnorderedSet<Key> &toSet, const Key& initial): values(toSet), initial_value(initial) {}

        /**
         * @brief Constructor that sets the values of the data node by tokenizing a string.
         * @param valuesToSet The string containing the values to be set.
         */
        explicit DataProps(const Key &valuesToSet) {
            NodeProps::tokenize(valuesToSet, ',', values);
        }

        /**
         * @brief Constructor that sets the values and initial value of the data node by tokenizing a string.
         * @param valuesToSet The string containing the values to be set.
         * @param initial The initial value to be set.
         */
        explicit DataProps(const Key &valuesToSet, const Key& initial): initial_value(initial) {
            NodeProps::tokenize(valuesToSet, ',', values);
        }

        /**
         * @brief Overloaded stream insertion operator to print the DataProps object to the output stream.
         * @param os Reference to the output stream object.
         * @param data The DataProps object to be printed.
         * @return The output stream object.
         */
        friend std::ostream &operator<<(std::ostream &os, const DataProps &data) {
            os << static_cast<const NodeProps &>(data);
            os << "values ["<<data.values.size()<<"] :: ";
            for (auto &value : data.values) {
                os<<value<<", ";
            }
            os << ":: initial_value: " << data.initial_value << "\n";
            return os;
        }

    };
}
