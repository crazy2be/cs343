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
    std::cout << 
        "Running test with:\n"
        "c.sodaCost = "<<c.sodaCost<<";\n" <<
        "c.numStudents = "<<c.numStudents<<";\n" <<
        "c.maxPurchases = "<<c.maxPurchases<<";\n" <<
        "c.numVendingMachines = "<<c.numVendingMachines<<";\n" <<
        "c.maxStockPerFlavour = "<<c.maxStockPerFlavour<<";\n" <<
        "c.maxShippedPerFlavour = "<<c.maxShippedPerFlavour<<";\n" <<
        "c.timeBetweenShipments = "<<c.timeBetweenShipments<<";\n" <<
        "c.parentalDelay = "<<c.parentalDelay<<";\n" <<
        "c.numCouriers = "<<c.numCouriers<<";\n\n"
    ;

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