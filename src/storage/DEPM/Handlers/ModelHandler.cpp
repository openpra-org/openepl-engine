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

#include <storm-parsers/api/storm-parsers.h>
#include <storm/api/storm.h>

#include "ModelHandler.h"
#include "api/openepl.h"


namespace OpenEPL::DEPM {

    ModelHandler::ModelHandler(const std::string &xml_path) : depm_xml_path(xml_path) {
        model = OpenEPL::api::parse(depm_xml_path);
        program = OpenEPL::api::getPrismProgram(*model);
    }

    bool ModelHandler::containsFormula(const std::string &formula) const {
        const auto &failureTerms = model->getProperties().failures;
        return (failureTerms.find(formula) != failureTerms.end());
    }

    std::string ModelHandler::buildMTTFPropertyString(const std::string &formula) {
        return "R{\"time\"}=? [ F "+formula+"]";
    }

    std::string ModelHandler::buildSteadyStateProbabilityString(const std::string &formula) {
        return "P=? [ F "+formula+"]";
    }

    std::string ModelHandler::buildProbabilityAtTimeString(const std::string &formula, const unsigned long time_step, const unsigned long step_length) {
        auto step = std::to_string(time_step * step_length);
        if (time_step == 1 && step_length == 1) {
            step = "step";
        }
        return "P=? [ F<="+step+" "+formula+"]";
    }

    std::vector<std::shared_ptr<storm::logic::Formula const>> ModelHandler::buildFormulae(const std::string &property_string) {

        // Then parse the properties, passing the program to give context to some potential variables.
        auto properties = storm::api::parsePropertiesForPrismProgram(property_string, *program);

        // Translate properties into the more low-level formulae.
        auto formulae = storm::api::extractFormulasFromProperties(properties);

        return formulae;
    }

    std::vector<std::shared_ptr<storm::logic::Formula const>> ModelHandler::getFormulaSteadyStateProbability(const std::string &formula) {
        auto formulae = std::vector<std::shared_ptr<const storm::logic::Formula>>();
        if (containsFormula(formula)) {
            return buildFormulae(ModelHandler::buildSteadyStateProbabilityString(formula));
        }
        return formulae;
    }

    std::vector<std::shared_ptr<storm::logic::Formula const>> ModelHandler::getFormulaMTTF(const std::string &formula) {
        auto formulae = std::vector<std::shared_ptr<const storm::logic::Formula>>();
        if (containsFormula(formula)) {
            return buildFormulae(ModelHandler::buildMTTFPropertyString(formula));
        }
        return formulae;
    }

    std::vector<std::shared_ptr<storm::logic::Formula const>> ModelHandler::getFormulaProbabilityAtTime(const std::string &formula, const unsigned long time_step, const unsigned long step_length) {
        auto formulae = std::vector<std::shared_ptr<const storm::logic::Formula>>();
        if (containsFormula(formula)) {
            return buildFormulae(ModelHandler::buildProbabilityAtTimeString(formula, time_step, step_length));
        }
        return formulae;
    }

}
