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
 * @file MapHandler.h
 * @brief This file contains the declaration of the MapHandler class.
 */

#pragma once
#include "utility/UnorderedMap.h"
#include "storage/DEPM/Model.h"

namespace OpenEPL::DEPM {
    /**
     * @brief A class template for handling a map of nodes.
     * @tparam NodeType The type of the node in the map.
     * @tparam NodePropsType The type of the properties of the node.
     */
    template <class NodeType, class NodePropsType> class MapHandler {
    protected:
        UnorderedMap<Key, NodeType> &map; /**< The map of nodes. */
    public:
        /**
         * @brief Constructs a MapHandler object.
         * @param map The map of nodes to be handled.
         */
        explicit MapHandler(UnorderedMap<Key, NodeType> &map): map(map) {}

        /**
         * @brief Removes a node from the map.
         * @param key The key of the node to be removed.
         * @return The number of nodes removed (0 or 1).
         */
        size_t remove(const Key& key) {
            return map.erase(key);
        }

        /**
         * @brief Retrieves a node from the map.
         * @param key The key of the node to be retrieved.
         * @return The retrieved node.
         * @throws std::out_of_range if the key is not found in the map.
         */
        NodeType &get(const Key& key) {
            return map.at(key);
        }

        /**
         * @brief Retrieves a node from the map if it exists, otherwise creates a new node.
         * @param key The key of the node to be retrieved or created.
         * @param node The node to be created if it does not exist.
         * @return The retrieved or created node.
         */
        NodeType &get_or_create(const Key& key, const NodeType &node) {
            return create(key, node);
        }

        /**
         * @brief Retrieves a node from the map if it exists, otherwise creates a new node.
         * @param key The key of the node to be retrieved or created.
         * @param nodeProps The properties of the node to be created if it does not exist.
         * @return The retrieved or created node.
         */
        NodeType &get_or_create(const Key& key, const NodePropsType &nodeProps) {
            return create(key, nodeProps);
        }

        /**
         * @brief Inserts a node into the map.
         * @param key The key of the node to be inserted.
         * @param node The node to be inserted.
         * @return The inserted node.
         */
        NodeType &insert(const Key& key, const NodeType &node) {
            return map.insert_or_assign(key, node).first->second;
        }

        /**
         * @brief Creates a new node with the given properties and inserts it into the map.
         * @param key The key of the node to be created and inserted.
         * @param nodeProps The properties of the node to be created.
         * @return The created and inserted node.
         */
        NodeType &create(const Key& key, const NodePropsType &nodeProps) {
            return insert(key, build(nodeProps));
        }

        /**
         * @brief Creates a new node with the given type and inserts it into the map.
         * @param key The key of the node to be created and inserted.
         * @param nodeType The type of the node to be created.
         * @return The created and inserted node.
         */
        NodeType &create(const Key& key, const NodeType &nodeType) {
            return insert(key, build(nodeType));
        }

        /**
         * @brief Swaps a node in the map with a new node.
         * @param key The key of the node to be swapped.
         * @param swapIn The new node to be swapped in.
         * @return The swapped out node.
         */
        NodeType &swap(const Key& key, const NodeType& swapIn) {
            auto swapOut = map.extract(key);
            map.insert_or_assign(key, swapIn);
            return swapOut.mapped();
        }

        /**
         * @brief Sets the properties of a node.
         * @param nodeType The node to set the properties for.
         * @param props The new properties for the node.
         * @return The updated node.
         */
        NodeType &setProperties(NodeType &nodeType, NodePropsType& props) {
            nodeType.props = props;
            return nodeType;
        }

        /**
         * @brief Retrieves the properties of a node.
         * @param node The node to retrieve the properties from.
         * @return The properties of the node.
         */
        NodePropsType &getProperties(NodeType &node) {
            return node.props;
        }

        /**
         * @brief Builds a new node with default properties.
         * @return The new node.
         */
        NodeType build() {
            return NodeType(NodePropsType());
        }

        /**
         * @brief Builds a new node with the given properties.
         * @param propsType The properties for the new node.
         * @return The new node.
         */
        NodeType build(const NodePropsType &propsType) {
            return NodeType(propsType);
        }

        /**
         * @brief Builds a new node with the same type as the given node.
         * @param nodeType The node to copy the type from.
         * @return The new node.
         */
        NodeType build(const NodeType &nodeType) {
            return NodeType(nodeType);
        }
    };
}
