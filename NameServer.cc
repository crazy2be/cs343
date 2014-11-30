#include "NameServer.h"

#include "VendingMachine.h"

#include "debug.h"

void NameServer::VMregister(VendingMachine * vendingMachine) {
    //We expect them in order, probably is not really needed.
    // But it's useful for my sanity too- it gaurentees we can't add the same
    // vending machine twice (well, unless we have vending machines with
    // duplicate IDs, but then we are really fucked).
    dassert(vendingMachine->getId() == (int)vendingMachines.size());

    vendingMachines.push_back(vendingMachine);
}

static int mod(int num, int base) {
    return ((num % base) + base) % base;
}

VendingMachine* NameServer::getMachine(int sid) {
    int vid = studentMachines[sid];

    studentMachines[sid] = mod(studentMachines[sid] + 1, numVendingMachines);

    return vendingMachines[vid];
}

VendingMachine ** NameServer::getMachineList() {
    return vendingMachines.data();
}

void NameServer::main() {

}
