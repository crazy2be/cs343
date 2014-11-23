#pragma once

_Task VendingMachine;

_Task NameServer {
    void main();
  public:
    NameServer(Printer &prt, int numVendingMachines, int numStudents);
    void VMregister(VendingMachine *vendingmachine);
    VendingMachine *getMachine(int id);
    VendingMachine **getMachineList();
};
