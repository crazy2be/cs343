#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
private:
    Printer& printer;
    NameServer& nameServer;
    BottlingPlant& plant;
    int numVendingMachines;
    int maxStockPerFlavour;

public:
    Truck(Printer &printer, NameServer &nameServer, BottlingPlant &plant,
             int numVendingMachines, int maxStockPerFlavour)
    : printer(printer), nameServer(nameServer), plant(plant),
      numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) { }

private:
    void main();
};
