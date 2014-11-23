#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
    void main();
  public:
    Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
          int numVendingMachines, int maxStockPerFlavour);
};
