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
/**
 * @file
 * @brief This file contains the EPCProps and EPC classes for the OpenEPL::DEPM namespace.
 */
#include "NodeProps.h"

namespace OpenEPL::DEPM {

    /**
     * @brief EPCProps is a struct that inherits from NodeProps and represents the properties of an EPC node.
     */
    struct EPCProps : public NodeProps {
    public:
        Key expression; ///< The expression associated with the EPC node.

        /**
         * @brief Default constructor for EPCProps.
         */
        explicit EPCProps() = default;

        /**
         * @brief Constructor for EPCProps that sets the expression.
         * @param toSet The expression to set.
         */
        explicit EPCProps(const Key& toSet): expression(toSet) {}

        /**
         * @brief Overloaded stream insertion operator for EPCProps.
         * @param os The output stream.
         * @param epc The EPCProps object to insert into the stream.
         * @return The modified output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const EPCProps &epc) {
            os << static_cast<const NodeProps &>(epc);
            os << "expression: " << epc.expression;
            return os;
        }
    };

}
