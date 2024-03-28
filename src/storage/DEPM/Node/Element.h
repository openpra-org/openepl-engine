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
 * @file Element.h
 * @brief Contains the declaration of the Element class.
 */

#pragma once

#include <set>
#include <ostream>
#include <utility>
#include <boost/property_tree/ptree.hpp>

#include "utility/UnorderedMap.h"
#include "utility/ContainerTypes.h"

#include "Node.h"
#include "CFC.h"
#include "EPC.h"
#include "storage/DEPM/NodeProps/ElementProps.h"

namespace OpenEPL::DEPM {
    /**
     * @class Element
     * @brief Represents an element in the DEPM
     * @tparam ElementProps The type of properties associated with the element.
     */
    class Element : public Node<ElementProps> {
        friend class ModelHandler;
        template<class N, class P> friend class NodeTest;

    protected:
        /**
         * @brief Default constructor for the Element class.
         */
        explicit Element(): Node<ElementProps>() {};

    public:
        /**
         * @brief Constructor for the Element class.
         * @param props The properties associated with the element.
         */
        explicit Element(const ElementProps &props) : Node<ElementProps>(props) {}
    };
}
