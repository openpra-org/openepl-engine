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

#include <memory>
#include <vector>

#include <storm/storage/jani/Property.h>
#include <storm/storage/prism/Program.h>

#include "storage/DEPM/Model.h"
#include "utility/UnorderedMap.h"

namespace OpenEPL::Test::DEPM {
    class ModelTransformerTest;
}

namespace OpenEPL::DEPM {
    /**
     * @class ModelTransformer
     * @brief The ModelTransformer class is responsible for transforming an OpenEPL DEPM model into a Storm implemented
     * Prism Program.
     */
    class ModelTransformer {
        friend class ModelTransformerTest;
    public:
        /**
         * @brief Builds a Prism Program from a given DEPM model.
         * @param model The DEPM model to be transformed.
         * @return A shared pointer to the generated Prism Program.
         */
        static std::shared_ptr<storm::prism::Program> buildProgram(const Model &model);

        /**
         * @brief Builds a vector of JANI properties from a given DEPM model.
         * @param model The DEPM model to be transformed.
         * @return A vector of JANI properties.
         */
        static std::vector<storm::jani::Property> buildProperties(const Model &model);

    protected:
        /**
         * @brief Generates element constants for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A string containing the element constants.
         */
        static std::string generate_element_constants(const Model &model);

        /**
         * @brief Generates failure formulas for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A string containing the failure formulas.
         */
        static std::string generate_failure_formulas(const Model &model);

        /**
         * @brief Generates the control flow module for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A string containing the control flow module.
         */
        static std::string generate_control_flow_module(const Model &model);

        /**
         * @brief Generates default control flow commands for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @param el_name The name of the element for which to generate the commands.
         * @return A string containing the default control flow commands.
         */
        static std::string generate_default_cf_commands(const Model &model, const std::string &el_name);

        /**
         * @brief Generates the error propagation module for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A string containing the error propagation module.
         */
        static std::string generate_error_propagation_module(const Model &model);

        /**
         * @brief Generates data value constants for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A string containing the data value constants.
         */
        static std::string generate_data_value_constants(const Model &model);

        /**
         * @brief Generates time rewards for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A string containing the time rewards.
         */
        static std::string generate_time_reward(const Model &model);

        /**
         * @brief Encodes string values for the Prism Program.
         * @param model The DEPM model to be transformed.
         * @return A map containing the encoded string values.
         */
        static std::map<int, std::string> encode_string_values(const Model &model);

        /**
         * @brief Separates integer and string values from the DEPM model.
         * @param model The DEPM model to be transformed.
         * @return A pair containing a vector of string values and a set of integer values.
         */
        static std::pair<std::vector<std::string>, std::set<int>> separate_int_and_str_values(const Model &model);

        /**
         * @brief Gets the maximum value from the DEPM model.
         * @param model The DEPM model to be transformed.
         * @return The maximum value.
         */
        static size_t get_maximum_value(const Model &model);
    };
}
