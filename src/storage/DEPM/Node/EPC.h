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
#include "storage/DEPM/NodeProps/EPCProps.h"

namespace OpenEPL::DEPM {

    /**
     * @brief EPC is a class that inherits from Node<EPCProps> and represents an EPC node in the DEPM model.
     */
    class EPC : public Node<EPCProps> {
        friend class ModelHandler;
        template<class N, class P> friend class NodeTest;

    protected:
        /**
         * @brief Default constructor for EPC.
         */
        explicit EPC(): Node<EPCProps>() {};

    public:
        /**
         * @brief Constructor for EPC that sets the properties.
         * @param props The EPCProps object to set.
         */
        explicit EPC(const EPCProps &props) : Node<EPCProps>(props) {}

        /**
         * @brief Equality operator for EPC.
         * @param rhs The EPC object to compare with.
         * @return True if the expressions are equal, false otherwise.
         */
        bool operator==(const EPC &rhs) const {
            return props.expression == rhs.props.expression;
        }

        /**
         * @brief Inequality operator for EPC.
         * @param rhs The EPC object to compare with.
         * @return True if the expressions are not equal, false otherwise.
         */
        bool operator!=(const EPC &rhs) const {
            return !(rhs == *this);
        }

        /**
         * @brief Less than operator for EPC.
         * @param rhs The EPC object to compare with.
         * @return True if the expression is less than rhs's expression, false otherwise.
         */
        bool operator<(const EPC &rhs) const {
            return props.expression < rhs.props.expression;
        }

        /**
         * @brief Greater than operator for EPC.
         * @param rhs The EPC object to compare with.
         * @return True if the expression is greater than rhs's expression, false otherwise.
         */
        bool operator>(const EPC &rhs) const {
            return rhs < *this;
        }

        /**
         * @brief Less than or equal to operator for EPC.
         * @param rhs The EPC object to compare with.
         * @return True if the expression is less than or equal to rhs's expression, false otherwise.
         */
        bool operator<=(const EPC &rhs) const {
            return !(rhs < *this);
        }

        /**
         * @brief Greater than or equal to operator for EPC.
         * @param rhs The EPC object to compare with.
         * @return True if the expression is greater than or equal to rhs's expression, false otherwise.
         */
        bool operator>=(const EPC &rhs) const {
            return !(*this < rhs);
        }
    };
}
