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
    Truck(Printer & prt, NameServer & nameServer, BottlingPlant & plant,
    int numVendingMachines, int maxStockPerFlavour);

private:
    void main();
};
