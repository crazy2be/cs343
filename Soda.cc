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

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// This isn'nt neende we should delete it.
void handler(int sig) {
    void *array[100];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 100);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void uMain::main() {
    signal(SIGSEGV, handler);   // install our handler

    Config config;
    // TODO: soda.config should be argv[0]
    readConfigFile("soda.config", config);

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


        std::cout << "Created all the shit!" << std::endl;
        // loop()


        for (int i = 0; i < (int)students.size(); i++) {
            delete students[i];
        }
    }

    for (int i = 0; i < (int)machines.size(); i++) {
        delete machines[i];
    }
}
