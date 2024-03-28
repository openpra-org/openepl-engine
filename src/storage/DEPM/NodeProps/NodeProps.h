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
* @file NodeProps.h
* @brief This file contains the declaration of the NodeProps classes, which is used to represent nodes data
* the OpenEPL DEPM model.
*/
#pragma once

#include <sstream>
#include <ostream>

#include "utility/ContainerTypes.h"

namespace OpenEPL::DEPM {
    /**
     * @brief The NodeProps struct represents the properties of a node in the OpenEPL DEPM model.
     */
    struct NodeProps {
        template<class PropsType> friend class PropsTest;

    public:
        Key name; ///< The name of the node.

        /**
         * @brief Default constructor for NodeProps.
         */
        explicit NodeProps() = default;

        /**
         * @brief Constructs a new NodeProps object with the given name.
         * @param name The name of the node.
         */
        explicit NodeProps(const Key &name) : name(const_cast<Key &>(name)) {}

        /**
         * @brief Tokenizes the given string using the specified delimiter and stores the tokens in the provided container.
         * @param str The string to be tokenized.
         * @param delim The delimiter to be used for tokenization.
         * @param container The container to store the tokens.
         */
        static void tokenize(const Key &str, const char delim, UnorderedSet<Key> &container) {
            std::stringstream dataStream(str);
            while(dataStream.good())
            {
                std::string substr;
                std::getline(dataStream, substr, delim);
                container.insert(substr);
            }
        }

        /**
         * @brief Tokenizes the given string using the default delimiter (comma) and stores the tokens in the provided container.
         * @param str The string to be tokenized.
         * @param container The container to store the tokens.
         */
        static void tokenize(const Key &str, UnorderedSet<Key> &container) {
            NodeProps::tokenize(str, ',', container);
        }

        /**
         * @brief Overloads the stream insertion operator for NodeProps objects.
         * @param os The output stream to insert the NodeProps object into.
         * @param node The NodeProps object to be inserted into the output stream.
         * @return The output stream with the NodeProps object inserted.
         */
        friend std::ostream &operator<<(std::ostream &os, const NodeProps &node) {
            return os;
        }
    };
}
