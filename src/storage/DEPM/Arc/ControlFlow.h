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
 * @file ControlFlow.h
 * @brief This file contains the declaration of the ControlFlow class and its associated structures.
 */

#pragma once
#include <ostream>

#include "storage/DEPM/Arc/Arc.h"
#include "storage/DEPM/Node/Element.h"

namespace OpenEPL::DEPM {
    /**
     * @brief Structure that represents the properties of a control flow arc.
     * @details This structure inherits from ArcProps.
     */
    struct ControlFlowProps : public ArcProps {
        friend class ControlFlowPropsTest;
    };
}

namespace OpenEPL::DEPM {
    /**
     * @brief Class that represents a control flow arc.
     * @details This class inherits from Arc<ControlFlowProps>.
     */
    class ControlFlow : public Arc<ControlFlowProps> {
        friend class ModelHandler;
        friend class ControlFlowTest;
    protected:
    public:
        /**
         * @brief Constructor for ControlFlow class.
         * @param arcProps The properties of the control flow arc.
         */
        explicit ControlFlow(const ControlFlowProps &arcProps): Arc<ControlFlowProps>(arcProps) {}

        /**
         * @brief Overloaded stream insertion operator for ControlFlow class.
         * @param os The output stream.
         * @param flow The ControlFlow object to be inserted into the stream.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const ControlFlow &flow) {
            os<<static_cast<const Arc<ControlFlowProps> &>(flow);
            return os;
        }
    };
}
