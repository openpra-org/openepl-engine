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
 * @file ContainerTypes.h
 * @brief This file contains the declaration of various container types used in the OpenEPL DEPM model.
 */
#pragma once

#include <set>
#include <map>
#include <unordered_set>
#include <string>

#include <iostream>

namespace OpenEPL::DEPM {
    /**
     * @brief A type alias for a basic string of characters.
     */
    typedef std::string Key;

    /**
     * @brief A type alias for a pair of Key and ValueType.
     * @tparam ValueType The type of the value in the pair.
     */
    template<class ValueType> using Pair = std::pair<Key, ValueType>;

    /**
     * @brief A type alias for a map with Key as the key type and ValueType as the value type.
     * @tparam ValueType The type of the value in the map.
     */
    template<class ValueType> using Map = std::map<Key, ValueType>;

    /**
     * @brief A type alias for a set of ValueType elements.
     * @tparam ValueType The type of the elements in the set.
     */
    template<class ValueType> using Set = std::set<ValueType>;

    /**
     * @brief A type alias for an unordered set of ValueType elements.
     * @tparam ValueType The type of the elements in the unordered set.
     */
    template<class ValueType> using UnorderedSet = std::unordered_set<ValueType>;
}
