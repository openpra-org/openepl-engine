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
 * @file UnorderedMap.h
 * @brief Declaration of the UnorderedMap class, which is a custom implementation of the
 * std::unordered_map with additional functionality.
 */

#pragma once

#include <unordered_map>
#include <iostream>

namespace OpenEPL::DEPM {
    /**
     * @brief The UnorderedMap class is a custom implementation of the std::unordered_map with additional functionality.
     * @tparam K The key type of the unordered map.
     * @tparam V The value type of the unordered map.
     */
    template<class K, class V>
    class UnorderedMap : public std::unordered_map<K, V> {
    public:

        /**
         * @brief Retrieves the value associated with the given key, or returns the provided default value if the key
         * is not found.
         * @param _k The key to search for in the unordered map.
         * @param _default The default value to return if the key is not found.
         * @return The value associated with the key, or the default value if the key is not found.
         */
        V& at(const K &_k, const V &_default) {
            try {
                return std::unordered_map<K,V>::at(_k);
            } catch (std::exception &e) {
                std::cerr << "unable to find key: " << _k << " in UnorderedMap\n";
            }
            return _default;
        };

        /**
         * @brief Retrieves the value associated with the given key, or throws an exception if the key is not found.
         * @param _k The key to search for in the unordered map.
         * @return The value associated with the key.
         * @throws std::exception If the key is not found in the unordered map.
         */
        V& at(const K &_k) {
            try {
                return std::unordered_map<K,V>::at(_k);
            } catch (std::exception &e) {
                std::cerr << "unable to find key: " << _k << " in UnorderedMap\n";
                throw e;
            }
        };
    };
}
