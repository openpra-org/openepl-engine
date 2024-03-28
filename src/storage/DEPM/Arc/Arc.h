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
 * @file
 * @brief This file contains the definition of the ArcProps struct and the Arc class.
 */

#pragma once
#include <ostream>
#include "storage/DEPM/Node/Node.h"
#include "utility/ContainerTypes.h"

namespace OpenEPL::DEPM {
    /**
     * @brief The ArcProps struct represents the properties of an arc in a graph.
     */
    struct ArcProps {
        friend class ArcPropsTest;
    public:
        /**
         * @brief Default constructor for ArcProps.
         */
        explicit ArcProps() = default;

        /**
         * @brief Constructor for ArcProps.
         * @param source The source key of the arc.
         * @param sink The sink key of the arc.
         */
        explicit ArcProps(Key &source, Key &sink): source(source), sink(sink) {}

        Key source; /**< The source key of the arc. */
        Key sink; /**< The sink key of the arc. */

        /**
         * @brief Overloaded stream insertion operator to print the ArcProps object.
         * @param os Reference to the output stream object.
         * @param arc The ArcProps object to be printed.
         * @return The output stream object.
         */
        friend std::ostream &operator<<(std::ostream &os, const ArcProps &arc) {
            os << "from: " << arc.source << " to " << arc.sink << "\n";
            return os;
        }
    };
}

namespace OpenEPL::DEPM {
    /**
     * @brief The Arc class represents an arc in a graph.
     * @tparam ArcPropsType The type of the arc properties.
     */
    template<class ArcPropsType>
    class Arc {
        friend class ModelHandler;
        friend class ArcTest;
        template<class Type, class Props>friend class ArcHandler;

    protected:
        ArcPropsType props; /**< The properties of the arc. */

        /**
         * @brief Default constructor for Arc.
         */
        explicit Arc() { props = ArcPropsType(); }

    public:
        /**
         * @brief Constructor for Arc.
         * @param arcProps The properties of the arc.
         */
        explicit Arc(const ArcPropsType &arcProps) : props(arcProps) {}

        /**
         * @brief Get the properties of the arc.
         * @return The properties of the arc.
         */
        const ArcPropsType &getProperties() const { return props; }

        /**
         * @brief Overloaded less than operator for comparing arcs.
         * @param rhs The right-hand side arc to compare.
         * @return True if this arc is less than the rhs arc, false otherwise.
         */
        bool operator<(const Arc &rhs) const {
            return std::tie(props.source, props.sink) < std::tie(rhs.props.source, rhs.props.sink);
        }

        /**
         * @brief Overloaded greater than operator for comparing arcs.
         * @param rhs The right-hand side arc to compare.
         * @return True if this arc is greater than the rhs arc, false otherwise.
         */
        bool operator>(const Arc &rhs) const {
            return rhs < *this;
        }

        /**
         * @brief Overloaded less than or equal to operator for comparing arcs.
         * @param rhs The right-hand side arc to compare.
         * @return True if this arc is less than or equal to the rhs arc, false otherwise.
         */
        bool operator<=(const Arc &rhs) const {
            return !(rhs < *this);
        }

        /**
         * @brief Overloaded greater than or equal to operator for comparing arcs.
         * @param rhs The right-hand side arc to compare.
         * @return True if this arc is greater than or equal to the rhs arc, false otherwise.
         */
        bool operator>=(const Arc &rhs) const {
            return !(*this < rhs);
        }

        /**
         * @brief Overloaded equality operator for comparing arcs.
         * @param rhs The right-hand side arc to compare.
         * @return True if this arc is equal to the rhs arc, false otherwise.
         */
        bool operator==(const Arc &rhs) const {
            return std::tie(props.source, props.sink) == std::tie(rhs.props.source, rhs.props.sink);
        }

        /**
         * @brief Overloaded inequality operator for comparing arcs.
         * @param rhs The right-hand side arc to compare.
         * @return True if this arc is not equal to the rhs arc, false otherwise.
         */
        bool operator!=(const Arc &rhs) const {
            return !(rhs == *this);
        }

        /**
         * @brief Overloaded stream insertion operator to print the Arc object.
         * @param os Reference to the output stream object.
         * @param arc The Arc object to be printed.
         * @return The output stream object.
         */
        friend std::ostream &operator<<(std::ostream &os, const Arc &arc) {
            os<<arc.props;
            return os;
        }
    };
}
