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

#include "storage/DEPM/NodeProps/CFCProps.h"

namespace OpenEPL::DEPM {

    /**
     * @brief CFC is a class that inherits from Node<CFCProps> and represents an CFC node in the DEPM model.
     */
    class CFC : public Node<CFCProps> {
        friend class ModelHandler;
        template<class N, class P> friend class NodeTest;

    protected:
        /**
         * @brief Default constructor for CFC.
         */
        explicit CFC(): Node<CFCProps>() {};

    public:
        /**
         * @brief Constructor for CFC that sets the properties.
         * @param props The CFCProps object to set.
         */
        explicit CFC(const CFCProps &props) : Node<CFCProps>(props) {}

        /**
         * @brief Equality operator for CFC.
         * @param rhs The CFC object to compare with.
         * @return True if the expressions are equal, false otherwise.
         */
        bool operator==(const CFC &rhs) const {
            return props.expression == rhs.props.expression;
        }

        /**
         * @brief Inequality operator for CFC.
         * @param rhs The CFC object to compare with.
         * @return True if the expressions are not equal, false otherwise.
         */
        bool operator!=(const CFC &rhs) const {
            return !(rhs == *this);
        }

        /**
         * @brief Less than operator for CFC.
         * @param rhs The CFC object to compare with.
         * @return True if the expression is less than rhs's expression, false otherwise.
         */
        bool operator<(const CFC &rhs) const {
            return props.expression < rhs.props.expression;
        }

        /**
         * @brief Greater than operator for CFC.
         * @param rhs The CFC object to compare with.
         * @return True if the expression is greater than rhs's expression, false otherwise.
         */
        bool operator>(const CFC &rhs) const {
            return rhs < *this;
        }

        /**
         * @brief Less than or equal to operator for CFC.
         * @param rhs The CFC object to compare with.
         * @return True if the expression is less than or equal to rhs's expression, false otherwise.
         */
        bool operator<=(const CFC &rhs) const {
            return !(rhs < *this);
        }

        /**
         * @brief Greater than or equal to operator for CFC.
         * @param rhs The CFC object to compare with.
         * @return True if the expression is greater than or equal to rhs's expression, false otherwise.
         */
        bool operator>=(const CFC &rhs) const {
            return !(*this < rhs);
        }
    };
}
