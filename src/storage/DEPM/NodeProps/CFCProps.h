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
 * @brief This file contains the CFCProps and CFC classes for the OpenEPL::DEPM namespace.
 */
#include "NodeProps.h"

namespace OpenEPL::DEPM {

    /**
     * @brief CFCProps is a struct that inherits from NodeProps and represents the properties of an CFC node.
     */
    struct CFCProps : public NodeProps {
    public:
        Key expression; ///< The expression associated with the CFC node.

        /**
         * @brief Default constructor for CFCProps.
         */
        explicit CFCProps() = default;

        /**
         * @brief Constructor for CFCProps that sets the expression.
         * @param toSet The expression to set.
         */
        explicit CFCProps(const Key& toSet): expression(toSet) {}

        /**
         * @brief Overloaded stream insertion operator for CFCProps.
         * @param os The output stream.
         * @param cfc The CFCProps object to insert into the stream.
         * @return The modified output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const CFCProps &cfc) {
            os << static_cast<const NodeProps &>(cfc);
            os << "expression: " << cfc.expression;
            return os;
        }
    };

}
