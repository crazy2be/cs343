#pragma once

#include <vector>
#include "Printer.h"

_Task VendingMachine;

_Task NameServer {
private:
    Printer &printer;
    int numVendingMachines;
    int numStudents;
    std::vector<VendingMachine*> vendingMachines;
    //We keep track of the machine each student is at, and every
    //    time they ask for a machine give them the next machine.
    std::vector<int> studentMachines;
public:
    NameServer(Printer & printer, int numVendingMachines, int numStudents)
        : printer(printer), numVendingMachines(numVendingMachines), numStudents(numStudents) {
            for (int ix = 0; ix < numStudents; ix++) {
                studentMachines.push_back(ix);
            }
        }
    void VMregister(VendingMachine * vendingMachine);
    VendingMachine * getMachine(int sid);
    VendingMachine **getMachineList();
private:
    void main();
};
