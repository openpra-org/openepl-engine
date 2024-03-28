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
 * @file ParserTypes.h
 * @brief This file contains type definitions used by the OpenEPL parser.
 */
#pragma once

#include <iterator>
#include <utility>

#include <boost/property_tree/ptree.hpp>

#include "ContainerTypes.h"
#include "UnorderedMap.h"

namespace OpenEPL::parser {
    /**
     * @brief Alias for the OpenEPL DEPM key type.
     */
    typedef OpenEPL::DEPM::Key Key;

    /**
     * @brief Alias for the boost property tree type.
     */
    typedef boost::property_tree::ptree PropertyTree;

    /**
     * @brief Alias for the boost property tree type with OpenEPL DEPM keys.
     */
    typedef boost::property_tree::basic_ptree<Key, Key> TreeXML;

    /**
     * @brief Alias for the boost property tree type with std::string keys and values.
     */
    typedef boost::property_tree::basic_ptree<std::string, std::string, std::less<Key>>::value_type SubtreeXML;

    /**
     * @brief Alias for a key-value pair with OpenEPL DEPM keys and a boost property tree value.
     */
    typedef std::pair<const Key, TreeXML> KeyValuePair;
}
