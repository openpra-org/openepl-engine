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
 * @file transformer.h
 * @brief This file contains the declaration of the transformer api.
 */

#pragma once

#include <set>
#include "transformer/DEPM/ModelTransformer.h"

namespace storm {
    namespace prism {
        class Program;
    }
    namespace jani {
        class Property;
    }
}

/**
 * @namespace OpenEPL
 * @brief The main namespace for the OpenEPL project.
 */
namespace OpenEPL {

    /**
     * @namespace DEPM
     * @brief The namespace containing functions for working with DEPM models.
     */
    namespace DEPM {
        class Model;
    }

    /**
     * @namespace api
     * @brief The namespace containing API functions for working with OpenEPL.
     */
    namespace api {
        /**
         * @brief Get the PRISM program representation of a DEPM model.
         * @param model The DEPM model.
         * @return A shared pointer to the PRISM program.
         */
        std::shared_ptr<storm::prism::Program> getPrismProgram(const DEPM::Model &model);
    }
}
