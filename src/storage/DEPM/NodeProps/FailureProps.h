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
 * @file Failure.h
 * @brief This file contains the declaration of the FailureProps struct and the Failure class, which represent a failure
 * in the OpenEPL DEPM model.
 */
#pragma once

#include <iostream>
#include "storage/DEPM/Node/Node.h"

namespace OpenEPL::DEPM {
    /**
     * @brief The FailureProps struct represents the properties of a failure in the OpenEPL DEPM model.
     */
    struct FailureProps : public NodeProps {
    public:
        Key property; ///< The property associated with the failure.

        /**
         * @brief Constructs a new FailureProps object with default values.
         */
        explicit FailureProps() = default;

        /**
         * @brief Constructs a new FailureProps object with the given node properties.
         * @param nodeProps The node properties to be used.
         */
        explicit FailureProps(const NodeProps &nodeProps) : NodeProps(nodeProps) {}

        /**
         * @brief Constructs a new FailureProps object with the given property.
         * @param property The property to be used.
         */
        explicit FailureProps(const Key &property) : NodeProps(), property(const_cast<Key &>(property)) {}

        /**
         * @brief Constructs a new FailureProps object with the given node properties and property.
         * @param nodeProps The node properties to be used.
         * @param property The property to be used.
         */
        explicit FailureProps(const NodeProps &nodeProps, const Key &property) : NodeProps(nodeProps), property(const_cast<Key &>(property)) {}

        /**
         * @brief Overloads the output stream operator for printing a FailureProps object.
         * @param os The output stream object.
         * @param failure The FailureProps object being printed.
         * @return The output stream object.
         */
        friend std::ostream &operator<<(std::ostream &os, const FailureProps &failure) {
            os << static_cast<const NodeProps &>(failure) << "property: " << failure.property<<std::endl;
            return os;
        }
    };
}
