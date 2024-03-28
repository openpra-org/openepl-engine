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
#include <set>
#include <ostream>
#include <utility>
#include <boost/property_tree/ptree.hpp>

#include "utility/UnorderedMap.h"
#include "utility/ContainerTypes.h"
#include "NodeProps.h"
#include "storage/DEPM/Node/EPC.h"
#include "storage/DEPM/Node/CFC.h"

/**
 * @file ElementProps.h
 * @brief Contains the definition of the ElementProps struct.
 */

#pragma once

#include <set>
#include <ostream>
#include <utility>
#include <boost/property_tree/ptree.hpp>

#include "utility/UnorderedMap.h"
#include "utility/ContainerTypes.h"
#include "NodeProps.h"
#include "storage/DEPM/Node/EPC.h"
#include "storage/DEPM/Node/CFC.h"

namespace OpenEPL::DEPM {
    /**
     * @struct ElementProps
     * @brief Represents the properties of an element in the DEPM.
     * @details Inherits from NodeProps.
     */
    struct ElementProps : public NodeProps {
    public:
        bool initial = false; /**< Indicates if the element is initial. */
        double time = 0; /**< The time associated with the element. */
        Set<EPC> epcs = {}; /**< The set of EPCs associated with the element. */
        Set<CFC> cfcs = {}; /**< The set of CFCs associated with the element. */

        /**
         * @brief Default constructor for ElementProps.
         */
        explicit ElementProps() = default;

        /**
         * @brief Constructor for ElementProps with initial flag.
         * @param initial The initial flag value.
         */
        explicit ElementProps(bool initial): initial(initial) {}

        /**
         * @brief Constructor for ElementProps with EPCs and CFCs.
         * @param epcs The set of EPCs.
         * @param cfcs The set of CFCs.
         */
        explicit ElementProps(const Set<EPC>& epcs, const Set<CFC>& cfcs): epcs(epcs), cfcs(cfcs) {}

        /**
         * @brief Constructor for ElementProps with EPCs and initial flag.
         * @param epcs The set of EPCs.
         * @param initial The initial flag value.
         */
        explicit ElementProps(const Set<EPC>& epcs, bool initial): epcs(epcs), initial(initial) {}

        /**
         * @brief Overloaded stream insertion operator for ElementProps.
         * @param os The output stream.
         * @param element The ElementProps object to be inserted into the stream.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const ElementProps &element) {
            os << static_cast<const NodeProps &>(element);
            os << "epcs: ("<<element.epcs.size()<<"):\n[";
            for (auto &epc : element.epcs) {
                os<<epc<<",\n";
            }
            os << "];";
            os << "cfcs: ("<<element.cfcs.size()<<"):\n[";
            for (auto &cfc : element.cfcs) {
                os<<cfc<<",\n";
            }
            os << "];";
            os << "time: " << element.time << ";\n";
            os << "initial: " << element.initial << ";\n";
            return os;
        }
    };
}
