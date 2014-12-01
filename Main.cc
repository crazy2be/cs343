#include "Main.h"

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

void runTest(Config c) {
    printf(
        "Running test with:\n"
        "c.sodaCost = %d;\n"
        "c.numStudents = %d;\n"
        "c.maxPurchases = %d;\n"
        "c.numVendingMachines = %d;\n"
        "c.maxStockPerFlavour = %d;\n"
        "c.maxShippedPerFlavour = %d;\n"
        "c.timeBetweenShipments = %d;\n"
        "c.parentalDelay = %d;\n"
        "c.numCouriers = %d;\n\n",
        c.sodaCost,
        c.numStudents,
        c.maxPurchases,
        c.numVendingMachines,
        c.maxStockPerFlavour,
        c.maxShippedPerFlavour,
        c.timeBetweenShipments,
        c.parentalDelay,
        c.numCouriers
    );

    Main(c);
}

void Main(Config& config) {
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