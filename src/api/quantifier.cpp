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
 * @brief This file contains the implementation of OpenEPL API functions for quantifying failure terms from a DEPM Model
 * XML.
 */
#include <set>
#include <fstream>
#include <limits>

#include <storm/api/storm.h>

#include <storm/storage/prism/Program.h>
#include <storm-parsers/api/storm-parsers.h>
#include <storm/logic/Formula.h>

#include "quantifier.h"
#include "transformer.h"
#include "parser.h"
#include "storage/DEPM/Handlers/ModelHandler.h"


typedef storm::models::sparse::Dtmc<double> Dtmc;
typedef storm::modelchecker::SparseDtmcPrctlModelChecker<Dtmc> DtmcModelChecker;

typedef storm::models::sparse::Ctmc<double> Ctmc;
typedef storm::modelchecker::SparseCtmcCslModelChecker<Ctmc> CtmcModelChecker;

#define PROBABILITY_INF std::numeric_limits<double>::infinity()

namespace OpenEPL::api {

    template <typename ModelType, typename CheckerType> double check(const storm::prism::Program &program, const std::vector<std::shared_ptr<storm::logic::Formula const>> &formulae) {
        // Now translate the prism program into a DTMC/CTMC in the sparse format.
        // Use the formulae to add the correct labelling.
        auto model = storm::api::buildSparseModel<double>(program, formulae)->template as<ModelType>();

        // Create a model checker on top of the sparse engine.
        auto checker = std::make_shared<CheckerType>(*model);

        for(auto &f : formulae) {
            std::cout<<"checking formula: "<<f->toString()+"\t";

            const auto onlyInitialStateRelevant = false;
            // Create a check task with the formula. Run this task with the model checker.
            auto result = checker->check(storm::modelchecker::CheckTask<>(*f, onlyInitialStateRelevant));
            assert(result->isExplicitQuantitativeCheckResult());

            // Use that we know that the model checker produces an explicit quantitative result
            auto quantRes = result->template asExplicitQuantitativeCheckResult<double>().getValueVector();
            return quantRes[*model->getInitialStates().begin()];
        }
        return PROBABILITY_INF;
    }

    namespace probability {
        double steadystate(std::string const &filename, std::string const &term) {
            auto handler = OpenEPL::DEPM::ModelHandler(filename);
            auto formulae = handler.getFormulaSteadyStateProbability(term);
            return check<Dtmc, DtmcModelChecker>(*handler.program, formulae);
        }

        double at(std::string const &filename, std::string const& term, unsigned long time_step, unsigned long step_length) {
            auto handler = OpenEPL::DEPM::ModelHandler(filename);
            auto formulae = handler.getFormulaProbabilityAtTime(term, time_step, step_length);
            return check<Dtmc, DtmcModelChecker>(*handler.program, formulae);
        }
    }

    namespace time {
        double mttf(std::string const &filename, std::string const &term, unsigned long step_length) {
            auto handler = OpenEPL::DEPM::ModelHandler(filename);
            auto formulae = handler.getFormulaMTTF(term);
            return check<Dtmc, DtmcModelChecker>(*handler.program, formulae);
        }

        double mtbf(std::string const &filename, std::string const& term, unsigned long step_length) {
            auto handler = OpenEPL::DEPM::ModelHandler(filename);
            auto formulae = handler.getFormulaMTTF(term);
            return check<Dtmc, DtmcModelChecker>(*handler.program, formulae);
        }
    }


    double checkProperty(std::string const& filename, std::string const& property_string) {

        // Parse Model from XML
        auto model_ptr = OpenEPL::api::parse(filename);
        if(!model_ptr) {
            std::cerr<<"Unable to quantify:: Parsing XML to DEPM Model failed"<<std::endl;
            return PROBABILITY_INF;
        }

        // transform Model to Program and Properties
        auto program = OpenEPL::DEPM::ModelTransformer::buildProgram(*model_ptr);

        // Then parse the properties, passing the program to give context to some potential variables.
        auto properties = storm::api::parsePropertiesForPrismProgram(property_string, *program);

        // Translate properties into the more low-level formulae.
        auto formulae = storm::api::extractFormulasFromProperties(properties);

        switch (program->getModelType()) {
            case storm::prism::Program::ModelType::DTMC:
                return check<Dtmc, DtmcModelChecker>(*program, formulae);

            case storm::prism::Program::ModelType::CTMC:
                return check<Ctmc, CtmcModelChecker>(*program, formulae);

            default:
                std::cerr<<"Unable to handle model of type:: "<<program->getModelType()<<std::endl;
                return PROBABILITY_INF;
        }
    }

}
