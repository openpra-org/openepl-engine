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
 * @file ModelHandler.h
 * @brief This file contains the declaration of the ModelHandler class.
 */

#pragma once

#include <utility>

#include <storm/storage/prism/Program.h>
#include <storm/logic/Formula.h>

#include "storage/DEPM/Node/Data.h"
#include "storage/DEPM/Node/Failure.h"
#include "storage/DEPM/Node/Element.h"
#include "storage/DEPM/Node/EPC.h"
#include "storage/DEPM/Model.h"

#include "storage/DEPM/Handlers/MapHandler.h"

namespace OpenEPL::DEPM {
    /**
     * @class ModelHandler
     * @brief The ModelHandler class is responsible for handling DEPM models.
     */
    class ModelHandler {
    protected:
        const std::string &depm_xml_path; /**< The path to the DEPM XML file. */

    private:
        /**
         * @brief Builds the MTTF property string for a given formula.
         * @param formula The formula for which the MTTF property string is to be built.
         * @return The MTTF property string.
         */
        [[nodiscard]] static std::string buildMTTFPropertyString(const std::string &formula);

        /**
         * @brief Builds the steady state probability property string for a given formula.
         * @param formula The formula for which the steady state probability property string is to be built.
         * @return The steady state probability property string.
         */
        [[nodiscard]] static std::string buildSteadyStateProbabilityString(const std::string &formula);

        /**
         * @brief Builds the probability at time property string for a given formula.
         * @param formula The formula for which the probability at time property string is to be built.
         * @param time_step The time step.
         * @param step_length The step length.
         * @return The probability at time property string.
         */
        [[nodiscard]] static std::string buildProbabilityAtTimeString(const std::string &formula, unsigned long time_step = 1, unsigned long step_length = 1);

        /**
         * @brief Builds a vector of formulae from a property string.
         * @param property_string The property string.
         * @return A vector of formulae.
         */
        std::vector<std::shared_ptr<storm::logic::Formula const>> buildFormulae(const std::string &property_string);

    public:
        std::shared_ptr<Model> model; /**< The DEPM model. */
        std::shared_ptr<storm::prism::Program> program; /**< The PRISM program. */

        /**
         * @brief Constructs a ModelHandler object with the given XML path.
         * @param xml_path The path to the DEPM XML file.
         */
        explicit ModelHandler(const std::string &xml_path);

        /**
         * @brief Checks if the model contains a formula.
         * @param formula_string The formula to check.
         * @return True if the model contains the formula, false otherwise.
         */
        [[nodiscard]] bool containsFormula(const std::string &formula_string) const;

        /**
         * @brief Gets the formulae for the MTTF property of a given formula.
         * @param formula The formula for which the MTTF formulae are to be retrieved.
         * @return A vector of formulae for the MTTF property.
         */
        std::vector<std::shared_ptr<storm::logic::Formula const>> getFormulaMTTF(const std::string &formula);

        /**
         * @brief Gets the formulae for the probability at time property of a given formula.
         * @param formula The formula for which the probability at time formulae are to be retrieved.
         * @param time_step The time step.
         * @param step_length The step length.
         * @return A vector of formulae for the probability at time property.
         */
        std::vector<std::shared_ptr<storm::logic::Formula const>> getFormulaProbabilityAtTime(const std::string &formula, unsigned long time_step = 1, unsigned long step_length = 1);

        /**
         * @brief Gets the formulae for the steady state probability property of a given formula.
         * @param formula The formula for which the steady state probability formulae are to be retrieved.
         * @return A vector of formulae for the steady state probability property.
         */
        std::vector<std::shared_ptr<storm::logic::Formula const>> getFormulaSteadyStateProbability(const std::string &formula);
    };
}
