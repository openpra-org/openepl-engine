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

#include <memory>
#include <algorithm>
#include <variant>

#include <storm/storage/jani/Property.h>
#include <storm/storage/prism/Program.h>
#include <storm-parsers/parser/PrismParser.h>

#include "ModelTransformer.h"

namespace OpenEPL::DEPM {
    std::vector<storm::jani::Property> ModelTransformer::buildProperties(const Model &model) {
        auto propertiesPtr = std::vector<storm::jani::Property>();
        return propertiesPtr;
    }

    std::shared_ptr<storm::prism::Program> ModelTransformer::buildProgram(const Model &model) {

        std::vector<double> init_values = {};
        std::string res = "dtmc\n";
        res += generate_element_constants(model);
        res += generate_data_value_constants(model);
        res += generate_control_flow_module(model);
        res += generate_error_propagation_module(model);
        res += generate_time_reward(model);
        res += generate_failure_formulas(model);
        res += "const int step = 0;\n";
        res += "const double T = 1;";

        auto program = storm::parser::PrismParser::parseFromString(res, "", true);
        auto programPtr = std::make_shared<storm::prism::Program>(program);
        return programPtr;
    }

    std::string ModelTransformer::generate_element_constants(const Model &model) {
        std::string res;
        bool has_final_elements = false;
        const auto &elements = model.getProperties().elements;
        int i = 0;
        for (const auto& el : elements) {
            res += "const int " + el.first + "=" + std::to_string(i) + ";\n";
            i++;
            if (model.getControlFlowsForSource(el.first).empty()) {
                has_final_elements = true;
            }
        }
        if (has_final_elements) {
            res += "const int stop=" + std::to_string(elements.size()) + ";\n";
        }
        return res;
    }

    std::pair<std::vector<std::string>, std::set<int>> ModelTransformer::separate_int_and_str_values(const Model &model) {
        std::vector<std::string> str_values;
        std::set<int> int_values;

        const UnorderedMap<Key, Data>& model_data = model.getProperties().data;
        for (const auto& data : model_data) {
            // data is a Map<str, Data>
            const Key& dataName = data.first;
            const UnorderedSet<Key>& dataValues = data.second.getProperties().values;
            for (const Key& value : dataValues) {
                try {
                    const int int_value = std::stoi(value);
                    int_values.insert(int_value);
                } catch(std::exception &e) {
                    if (std::find(str_values.begin(), str_values.end(), value) == str_values.end()) {
                        str_values.push_back(value);
                    }
                }
            }
        }
        std::sort(str_values.begin(), str_values.end());
        return {str_values, int_values};
    }

    size_t ModelTransformer::get_maximum_value(const Model &model) {
        const auto &separated_values = separate_int_and_str_values(model);
        const auto &int_values = separated_values.second;
        const size_t len_i = int_values.size();
        const size_t len_s = separated_values.first.size();
        const size_t max_i = len_i > 0 ? *std::max_element(int_values.begin(), int_values.end()) : 1;
        return std::max(max_i, len_s + len_i - 1);
    }

    std::map<int, std::string> ModelTransformer::encode_string_values(const Model &model) {
        auto separated_values = separate_int_and_str_values(model);
        std::vector<std::string> str_values = separated_values.first;
        std::set<int> int_values = separated_values.second;
        std::map<int, std::string> res;
        int i = 0;
        while (!str_values.empty()) {
            if (int_values.find(i) == int_values.end()) {
                res[i] = str_values.back();
                str_values.pop_back();
            }
            i++;
        }
        return res;
    }

    std::string ModelTransformer::generate_data_value_constants(const Model &model) {
        auto values = encode_string_values(model);
        std::string res = "//Data value constants\n";
        for (const auto& kv : values) {
            res += "const int " + kv.second + "=" + std::to_string(kv.first) + ";\n";
        }
        return res;
    }

    std::string ModelTransformer::generate_time_reward(const Model &model) {
        std::string res = "rewards \"time\"\n";
        const auto &elements = model.getProperties().elements;
        for (const auto& el : elements) {
            const auto &time = std::to_string(el.second.getProperties().time);
            res += "\tcf=" + el.first + ":" + time + ";\n";
        }
        res += "endrewards\n";
        return res;
    }

    std::string ModelTransformer::generate_control_flow_module(const OpenEPL::DEPM::Model &model) {
        std::string res = "// Control flow commands\n";
        res += "module control_flow\n";
        const auto &elements = model.getProperties().elements;

        // initial element
        const auto &initialElement = model.getProperties().initialElement.value();
        res += "\tcf:[0.." + std::to_string(elements.size()) + "] init " + initialElement + ";\n";

        // all other elements
        for (const auto& el : elements) {
            const std::string &el_name = el.first;
            const Element &element = el.second;
            const std::set<CFC> CFCs = element.getProperties().cfcs;
            // use defaults if empty
            if(CFCs.empty()) {
                res += "\t[" + el_name + "] " + generate_default_cf_commands(model, el_name) + "\n";
            } else {
                for (const auto& cfc : CFCs) {
                    res += "\t[" + el_name + "] " + cfc.getProperties().expression + "\n";
                }
            }
        }
        res += "endmodule\n";
        return res;
    }

    std::string ModelTransformer::generate_default_cf_commands(const OpenEPL::DEPM::Model &model, const std::string& el_name) {
        const std::unordered_map<Key, Element> &elements = model.getProperties().elements;
        const auto element_iterator = elements.find(el_name);
        if (element_iterator == elements.end()) {
            return "";
        }

        // starting state
        std::string res = "cf=" + element_iterator->first + " -> ";
        const auto controlFlows = model.getControlFlowsForSource(element_iterator->first);

        // ending state
        if(!controlFlows.empty()) {
            const auto totalOutFlows = double(controlFlows.size());
            const auto probabilitySplit = std::to_string(1.0 / totalOutFlows);
            for (const auto& controlFlow : controlFlows) {
                res += probabilitySplit + ":(cf'=" + controlFlow.getProperties().sink + ") + ";
            }
            res = res.substr(0, res.length() - 3) + ";";
        } else {
            res += "(cf'=stop);";
        }
        return res;
    }


    std::string ModelTransformer::generate_error_propagation_module(const OpenEPL::DEPM::Model &model) {

        const UnorderedMap<Key, Data> data = model.getProperties().data;
        const auto &max_value = std::to_string(get_maximum_value(model));

        std::string res = "module error_propagation\n";
        for (const auto& datum : data) {
            const std::string &d_name = datum.first;
            const Data &d_value = datum.second;
            res += "\t" + d_name + " : [0 .. " + max_value + "] init ";
            res += d_value.getProperties().initial_value + ";\n";
        }

        const UnorderedMap<Key, Element> &elements = model.getProperties().elements;
        for (const auto& el : elements) {
            const std::pair<std::set<DataFlow>, std::set<DataFlow>> &dataFlows = model.getDataFlows(el.first);

            // do nothing if element does not contain any data out flows
            const std::set<DataFlow> &outFlows = dataFlows.first;
            if (outFlows.empty()) {
                continue;
            }

            // do nothing if element does not contain any EPCs
            const std::set<EPC> &EPCs = el.second.getProperties().epcs;
            if (EPCs.empty()) {
                continue;
            }

            // empty string if initial element
            const auto &epc_name = (el.first == "initial") ? " " : el.first;
            for (const auto& epc : EPCs) {
                res += "\t[" + epc_name + "] " + epc.getProperties().expression + "\n";
            }
        }
        res += "endmodule\n";
        return res;
    }

    std::string ModelTransformer::generate_failure_formulas(const Model &model) {
        std::string res;
        for (const auto& f : model.getProperties().failures) {
            res += "formula " + f.first + " = (" + f.second.getProperties().property + ");\n";
        }
        //model.generate_formula_rewards(); // Assuming this method exists in the Model class
        return res;
    }
}
