#include "Config.h"
#include "Printer.h"
#include "Bank.h"
#include "Parent.h"
#include "WATCardOffice.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"

#include <iostream>

void argErr(char *argv0) {
    std::cerr << "Usage: " << argv0 << " [ config-file [ random-seed (> 0) ] ]"
        << std::endl;
    exit(1);
}

void uMain::main() {
    std::string configName = "soda.config";
    int seed = getpid();
    switch (argc) {
    case 3: seed = atoi(argv[2]);
    case 2: configName = argv[1];
    case 1: break;
    default: argErr(argv[0]);
    }
    if (seed < 0) argErr(argv[0]);

    Config config;
    readConfigFile(configName.c_str(), config);
    srand(seed);

    Printer printer(config.numStudents, config.numVendingMachines,
                    config.numCouriers);
    Bank bank(config.numStudents);
    Parent parent(printer, bank, config.numStudents, config.parentalDelay);
    WATCardOffice office(printer, bank, config.numCouriers);
    NameServer nameServer(printer, config.numVendingMachines, config.numStudents);

    std::vector<VendingMachine*> machines;
    for (int i = 0; i < config.numVendingMachines; i++) {
        VendingMachine *machine = new VendingMachine(printer, nameServer, i,
                                                     config.sodaCost,
                                                     config.maxStockPerFlavour);
        machines.push_back(machine);
    }

    {
        // We have to delete the BottlingPlant before the vending machines,
        // so we put it in it's own scope like so.
        BottlingPlant plant(printer, nameServer, config.numVendingMachines,
                            config.maxShippedPerFlavour,
                            config.maxStockPerFlavour,
                            config.timeBetweenShipments);

        std::vector<Student*> students;
        for (int i = 0; i < config.numStudents; i++) {
            Student *student = new Student(printer, nameServer, office, i,
                                           config.maxPurchases);
            students.push_back(student);
        }

        // loop () {
        //      We idle here waiting for all the students to finish.
        // }

        for (int i = 0; i < (int)students.size(); i++) {
            delete students[i];
        }
    }

    for (int i = 0; i < (int)machines.size(); i++) {
        delete machines[i];
    }
}
