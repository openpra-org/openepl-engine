#include <storm/api/storm.h>
#include <storm/utility/initialize.h>

#include <iostream>

#include <boost/program_options.hpp>
#include <regex>

//#include <openepl/utility/JSON.hpp>
#include "api/quantifier.h"
#include "utility/Helpers.h"

static const std::set<std::string> validMethods = {
        "compute_downtime",
        "compute_MTTF",
        "compute_N_failures",
        "compute_P",
        "compute_P_single",
        "compute_Property"
};

static void buildInputArguments(boost::program_options::options_description &generics) {
    generics.add_options()
            ("help,h", "= Show this help message")
            ("model,i", boost::program_options::value<std::string>()->required(), "= Path for input DEPM xml")
            ("method,m", boost::program_options::value<std::string>()->required()->notifier(
                    [&](const std::string &value) {
                        if (!validMethods.count(value)) {
                            throw boost::program_options::validation_error(
                                    boost::program_options::validation_error::invalid_option_value, "method", value);
                        }
                    }), "= Quantification method to execute")
            ("target,t", boost::program_options::value<std::string>()->required(), "= Failure term to quantify")
            ("results,o", boost::program_options::value<std::string>()->default_value("/dev/fd/1"), "= Path for results JSON")
            ("timestep,s", boost::program_options::value<long double>()->default_value(1.0f), "= Timestep for P(timestep)")
            ;
}

static void run(nlohmann::json &resultJSON, boost::program_options::variables_map &map) {

    const auto targetTerm = map["target"].as<std::string>();
    const auto inputFilePath = map["model"].as<std::string>();
    const auto methodName = map["method"].as<std::string>();
    const auto timestep = map["timestep"].as<long double>();

    resultJSON["model_filepath"] = inputFilePath;
    resultJSON["output"] = nlohmann::json::array();
    resultJSON["output"][0]["property"]["method"] = methodName;
    resultJSON["output"][0]["property"]["target"] = targetTerm;

    if(methodName == "compute_MTTF") {
        resultJSON["output"][0]["result"] = OpenEPL::api::time::mttf(inputFilePath, targetTerm);
    }

    else if(methodName == "compute_P_single") {
        resultJSON["output"][0]["result"] = OpenEPL::api::probability::steadystate(inputFilePath, targetTerm);
        resultJSON["output"][0]["property"]["timestep"] = "infinity";
    }

    else if(methodName == "compute_P") {
        resultJSON["output"][0]["result"] = OpenEPL::api::probability::at(inputFilePath, targetTerm, timestep);
        resultJSON["output"][0]["property"]["timestep"] = timestep;
    }

    else if(methodName == "compute_Property") {
        resultJSON["output"][0]["result"] = OpenEPL::api::checkProperty(inputFilePath, targetTerm);
    }
}

int main (int argc, char *argv[]) {
    // Init loggers
    storm::utility::setUp();
    // Set some settings objects.
    storm::settings::initializeAll("openepl-engine", "openepl-engine");

    boost::program_options::options_description options("Parameters");
    buildInputArguments(options);
    boost::program_options::variables_map variablesMap = boost::program_options::variables_map();
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), variablesMap);
    boost::program_options::notify(variablesMap);

    //if help, print options and exit
    if (variablesMap.count("help")) {
        std::cout<<"openepl-engine::\n";
        std::cout << options << "\n";
        exit(0);
    }

    nlohmann::json json;
    run(json, variablesMap);
    writeJSON(variablesMap["results"].as<std::string>(), json);

    exit(0);
}
