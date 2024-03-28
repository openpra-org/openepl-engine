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

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "json.hpp"

/**
 * @brief Checks if a file is writable.
 * @param filepath The path to the file.
 * @return True if the file is writable, false otherwise.
 */
static bool isFileWritable(const std::string &filepath) {
    const std::filesystem::path path(filepath);
    std::error_code ec; // For using the non-throwing overloads of functions below.
    if(exists(path,ec)) {
        if(std::filesystem::is_directory(path, ec)) {
            std::cerr << "Error: Provided path is a directory. "<<std::endl;
            return false;
        }
        return true;
    }
    return true;
}

/**
 * @brief Writes the given JSON data to a file at the specified file path.
 *
 * This function checks if the file is writable and opens it for writing. If the file cannot be opened,
 * an error message is displayed. The JSON data is then written to the file with pretty formatting
 * (indented with 4 spaces). A success message is displayed upon successful writing of the JSON data.
 *
 * @param filepath The path of the file to write the JSON data to.
 * @param data The JSON data to be written to the file.
 */
static void writeJSON(const std::string &filepath, nlohmann::json &data) {

    if(!isFileWritable(filepath)) {
        std::cerr<<"Error: Unable to write output JSON to path: "<<filepath<<std::endl;
        return;
    }

    // Open the CSV file for writing
    std::ofstream jsonFile(filepath);

    // Check if the file was opened successfully
    if (!jsonFile.is_open()) {
        std::cerr << "Error opening the output JSON file"<<filepath<< std::endl;
        return;
    }

    // Write the JSON data to the file
    jsonFile << data.dump(4);  // The '4' argument is for pretty formatting with 4 spaces
}

/**
 * @brief Converts a string to a long double number.
 *
 * This function attempts to convert a given string to a long double number.
 * If the string cannot be converted to a number (invalid argument), or if the
 * number is out of range for a double, an exception is thrown and an error message
 * is printed to the standard error stream.
 *
 * @param input The string to be converted to a long double number.
 * @return The converted long double number.
 * @throws std::invalid_argument If the string cannot be converted to a number.
 * @throws std::out_of_range If the number is out of range for a double.
 */
static long double asNumber(const std::string &input) {
    try {
        return std::stod(input);
    } catch (const std::invalid_argument &) {
        std::cerr << "Argument is invalid\n";
        throw;
    } catch (const std::out_of_range &) {
        std::cerr << "Argument is out of range for a double\n";
        throw;
    } catch (...) {
        throw;
    }
}
