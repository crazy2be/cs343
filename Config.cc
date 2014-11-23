#include "Config.h"
#include "debug.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;

static bool findNextName(ifstream &in, string &name) {
    for (;;) {
        in >> name;
        if (in.fail()) return false;
        if (name[0] == '#') {
            // Ignore the rest of the line, since it's commented.
            in.ignore(numeric_limits<int>::max(), '\n');
            continue;
        }
        return true;
    }
}
struct ConfigParam {
    const char *name;
    bool found;
    int &value;
};
static ConfigParam &findParam(vector<ConfigParam> &params, string &name) {
    for (int i = 0; i < (int)params.size(); i++) {
        if (params.at(i).name == name) {
            return params.at(i);
        }
    }
    cerr << "Error: Unrecognized constant name '" << name << "'" << endl;
    exit(EXIT_FAILURE);
}
void parseFile(ifstream &in, vector<ConfigParam> &params) {
    for (;;) {
        string name;
        if (!findNextName(in, name)) break;
        ConfigParam &param = findParam(params, name);

        if (param.found) {
            cerr << "Error: Duplicate constant '" << name << "'" << endl;
            exit(EXIT_FAILURE);
        }
        param.found = true;

        in >> param.value;
        if (param.value <= 0) {
            cerr << "Error: constant " << name << " must be positive. "
                << " (got " << param.value << ")" << endl;
            exit(EXIT_FAILURE);
        }
        if (in.fail()) break;
    }
    for (int i = 0; i < (int)params.size(); i++) {
        ConfigParam &param = params.at(i);
        if (!param.found) {
            cerr << "Error: parameter " << param.name << " was not specified."
                "All parameter names must be specified." << endl;
            exit(EXIT_FAILURE);
        }
    }
}
void readConfigFile(const char *configFile, Config &cparms) {
    vector<ConfigParam> params = {
        {"SodaCost", false, cparms.sodaCost},
        {"NumStudents", false, cparms.numStudents},
        {"MaxPurchases", false, cparms.maxPurchases},
        {"NumVendingMachines", false, cparms.numVendingMachines},
        {"MaxStockPerFlavour", false, cparms.maxStockPerFlavour},
        {"MaxShippedPerFlavour", false, cparms.maxShippedPerFlavour},
        {"TimeBetweenShipments", false, cparms.timeBetweenShipments},
        {"ParentalDelay", false, cparms.parentalDelay},
        {"NumCouriers", false, cparms.numCouriers},
    };
    try {
        ifstream in(configFile);
        parseFile(in, params);
    } catch (uFile::Failure) {
        cerr << "Error: could not open input file \"" << configFile << "\"" << endl;
        exit(EXIT_FAILURE);
    }
}
