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
* @file Node.h
* @brief This file contains the declaration of the Node classe, which is used to represent nodes in
* the OpenEPL DEPM model.
*/
#pragma once

#include <sstream>
#include <ostream>

#include "utility/ContainerTypes.h"
#include "storage/DEPM/NodeProps/NodeProps.h"

namespace OpenEPL::DEPM {
    /**
     * @brief The Node class represents a node in the OpenEPL DEPM model.
     * @tparam NodePropsType The type of the properties of the node.
     */
    template<class NodePropsType = NodeProps>
    class Node {
        friend class ModelHandler;
        template<class N, class P> friend class MapHandler;
        template<class N, class P> friend class NodeTest;

    protected:
        NodePropsType props;
        explicit Node() { props = NodePropsType(); }
    public:
        /**
         * @brief Constructs a new Node object with the given properties.
         * @param nodeProps The properties of the node being created.
         */
        explicit Node(const NodePropsType &nodeProps) : props(nodeProps) {}

        /**
         * @brief Returns the properties of the node.
         * @return The properties of the node.
         */
        const NodePropsType &getProperties() const { return props; }

        /**
         * @brief Overloads the less than operator for comparing two nodes.
         * @param lhs The left-hand side node being compared.
         * @param rhs The right-hand side node being compared.
         * @return True if the left-hand side node is less than the right-hand side node, false otherwise.
         */
        friend bool operator<(const Node &lhs, const Node &rhs) {
            return std::addressof(lhs) < std::addressof(rhs);
        }

        /**
         * @brief Overloads the greater than operator for comparing two nodes.
         * @param lhs The left-hand side node being compared.
         * @param rhs The right-hand side node being compared.
         * @return True if the left-hand side node is greater than the right-hand side node, false otherwise.
         */
        friend bool operator>(const Node &lhs, const Node &rhs) {
            return rhs < lhs;
        }

        /**
         * @brief Overloads the less than or equal to operator for comparing two nodes.
         * @param lhs The left-hand side node being compared.
         * @param rhs The right-hand side node being compared.
         * @return True if the left-hand side node is less than or equal to the right-hand side node, false otherwise.
         */
        friend bool operator<=(const Node &lhs, const Node &rhs) {
            return !(rhs < lhs);
        }

        /**
         * @brief Overloads the greater than or equal to operator for comparing two nodes.
         * @param lhs The left-hand side node being compared.
         * @param rhs The right-hand side node being compared.
         * @return True if the left-hand side node is greater than or equal to the right-hand side node, false otherwise.
         */
        friend bool operator>=(const Node &lhs, const Node &rhs) {
            return !(lhs < rhs);
        }

        /**
         * @brief Overloads the equality operator for comparing two nodes.
         * @param lhs The left-hand side node being compared.
         * @param rhs The right-hand side node being compared.
         * @return True if the left-hand side node is equal to the right-hand side node, false otherwise.
         */
        friend bool operator==(const Node &lhs, const Node &rhs) {
            return std::addressof(lhs) == std::addressof(rhs);
        }

        /**
         * @brief Overloads the inequality operator for comparing two nodes.
         * @param lhs The left-hand side node being compared.
         * @param rhs The right-hand side node being compared.
         * @return True if the left-hand side node is not equal to the right-hand side node, false otherwise.
         */
        friend bool operator!=(const Node &lhs, const Node &rhs) {
            return !(lhs == rhs);
        }

        /**
         * @brief Overloads the output stream operator for printing a node.
         * @param os The output stream object.
         * @param node The node being printed.
         * @return The output stream object.
         */
        friend std::ostream &operator<<(std::ostream &os, const Node &node) {
            os<<"["<<std::addressof(node)<<"] :: "<<node.props;
            return os;
        }
    };
}
