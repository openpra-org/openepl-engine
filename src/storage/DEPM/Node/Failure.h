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
 * @file Failure.h
 * @brief This file contains the declaration of the FailureProps struct and the Failure class, which represent a failure
 * in the OpenEPL DEPM model.
 */
#pragma once

#include <iostream>
#include "storage/DEPM/Node/Node.h"
#include "storage/DEPM/NodeProps/FailureProps.h"

namespace OpenEPL::DEPM {
    /**
     * @brief The Failure class represents a failure in the OpenEPL DEPM model.
     */
    class Failure : public Node<FailureProps> {
        template<class N, class P> friend class NodeTest;
    protected:
        /**
         * @brief Constructs a new Failure object with default values.
         */
        explicit Failure(): Node<FailureProps>() {};
    public:
        /**
         * @brief Constructs a new Failure object with the given properties.
         * @param props The properties of the failure being created.
         */
        explicit Failure(const FailureProps &props) : Node<FailureProps>(props) {}
    };
}
