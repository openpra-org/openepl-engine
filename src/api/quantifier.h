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
 * @file quantifier.h
 * @brief This file exposes OpenEPL API functions to quantify failure terms from a DEPM Model XML.
 */

#pragma once

#include <unordered_map>
#include <vector>
#include <string>

/**
 * @namespace OpenEPL::api
 * @brief The OpenEPL::api namespace contains functions for quantifying failure terms from a DEPM Model XML.
 */
namespace OpenEPL::api {

    /**
     * @namespace OpenEPL::api::time
     * @brief The OpenEPL::api::time namespace contains functions for calculating time-related metrics.
     */
    namespace time {

        /**
         * @brief Calculates the Mean Time to Failure (MTTF) for a given failure term in a DEPM Model XML.
         * @param filename The path to the DEPM Model XML file.
         * @param term The failure term to calculate MTTF for.
         * @param step_length The length of each time step. Default is 1.
         * @return The calculated MTTF value.
         */
        double mttf(std::string const& filename, std::string const& term, unsigned long step_length = 1);

        /**
         * @brief Calculates the Mean Time Between Failures (MTBF) for a given failure term in a DEPM Model XML.
         * @param filename The path to the DEPM Model XML file.
         * @param term The failure term to calculate MTBF for.
         * @param step_length The length of each time step. Default is 1.
         * @return The calculated MTBF value.
         */
        double mtbf(std::string const& filename, std::string const& term, unsigned long step_length = 1);
    }

    /**
     * @namespace OpenEPL::api::probability
     * @brief The OpenEPL::api::probability namespace contains functions for calculating probability-related metrics.
     */
    namespace probability {

        /**
         * @brief Calculates the steady state probability for a given failure term in a DEPM Model XML.
         * @param filename The path to the DEPM Model XML file.
         * @param term The failure term to calculate the steady state probability for.
         * @return The calculated steady state probability value.
         */
        double steadystate(std::string const& filename, std::string const& term);

        /**
         * @brief Calculates the probability of a failure term occurring at a specific time step in a DEPM Model XML.
         * @param filename The path to the DEPM Model XML file.
         * @param term The failure term to calculate the probability for.
         * @param time_step The specific time step to calculate the probability for.
         * @param step_length The length of each time step. Default is 1.
         * @return The calculated probability value.
         */
        double at(std::string const& filename, std::string const& term, unsigned long time_step, unsigned long step_length = 1);
    }

    /**
     * @brief Checks if a given property string is valid in a DEPM Model XML.
     * @param filename The path to the DEPM Model XML file.
     * @param property_string The property string to check.
     * @return True if the property string is valid, false otherwise.
     */
    double checkProperty(std::string const& filename, std::string const& property_string);
}
