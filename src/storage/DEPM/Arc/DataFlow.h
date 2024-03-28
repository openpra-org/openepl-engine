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
 * @file DataFlow.h
 * @brief This file contains the declaration of the DataFlow class and its associated structures.
 */

#pragma once
#include <ostream>

#include "storage/DEPM/Arc/Arc.h"
#include "storage/DEPM/Node/Node.h"

namespace OpenEPL::DEPM {
    /**
     * @brief Structure that holds properties specific to a DataFlow arc.
     * @details This structure inherits from the ArcProps structure.
     */
    struct DataFlowProps : public ArcProps {
        friend class DataFlowPropsTest;
    };
}

namespace OpenEPL::DEPM {
    /**
     * @brief Class that represents a DataFlow arc in the DEPM model.
     * @details This class inherits from the Arc class and provides additional functionality specific to DataFlow arcs.
     */
    class DataFlow : public Arc<DataFlowProps> {
        friend class ModelHandler;
        friend class DataFlowTest;
    protected:
        // No additional protected members
    public:
        /**
         * @brief Constructor for the DataFlow class.
         * @param arcProps The properties of the DataFlow arc.
         */
        explicit DataFlow(const DataFlowProps &arcProps) : Arc(arcProps) {}

        /**
         * @brief Overloaded stream insertion operator for the DataFlow class.
         * @param os The output stream.
         * @param flow The DataFlow object to be inserted into the stream.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const DataFlow &flow) {
            os << static_cast<const Arc<DataFlowProps> &>(flow);
            return os;
        }
    };
}
