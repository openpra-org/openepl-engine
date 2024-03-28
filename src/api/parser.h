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
 * @file parser.h
 * @brief This file contains the declaration of the parse function.
 */

#pragma once

#include <string>
#include <list>
#include <memory>

namespace OpenEPL {
    namespace DEPM {
        class Model;
    }

    namespace api {
        /**
         * @brief Parses the given file and returns a shared pointer to the parsed model.
         *
         * @param filename The name of the file to parse.
         * @return std::shared_ptr<OpenEPL::DEPM::Model> A shared pointer to the parsed model.
         */
        std::shared_ptr<OpenEPL::DEPM::Model> parse(std::string const& filename);
    }
}
