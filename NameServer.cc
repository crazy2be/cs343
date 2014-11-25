#include "NameServer.h"

#include "debug.h"

void NameServer::VMregister(VendingMachine * vendingMachine) {
	//We expect them in order, probably is not really needed.
	dassert(vendingMachine->getId() == vendingMachines.size());

	vendingMachines.push_back(vendingMachine);
}

int MOD(int num, int base) {
	return ((num % base) + base) % base;
}

VendingMachine* NameServer::getMachine(int sid) {
	int vid = studentMachines[sid];

	studentMachines[sid] = MOD(studentMachines[sid] + 1, numVendingMachines);

	return vendingMachines[vid];
}

VendingMachine ** NameServer::getMachineList() {
	return vendingMachines.data();
}

void NameServer::main() {

}