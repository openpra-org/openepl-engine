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
 * @file handler.h
 * @brief This file contains the declaration of the OpenEPL namespace, which includes the DEPM namespace and the api namespace.
 */

#pragma once

namespace OpenEPL {
    namespace DEPM {
        class Model; // Forward declaration of the Model class
        class ModelHandler; // Forward declaration of the ModelHandler class
    }

    namespace api {
        /**
         * @brief Retrieves the ModelHandler for a given Model.
         *
         * @param model The Model for which to retrieve the ModelHandler.
         * @return The ModelHandler associated with the given Model.
         */
        DEPM::ModelHandler getModelHandler(DEPM::Model &model);
    }
}
