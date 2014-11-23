#pragma once

#include "Printer.h"
#include "NameServer.h"

_Task BottlingPlant {
    void main();
  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant(Printer &prt, NameServer &nameServer, int numVendingMachines,
                 int maxShippedPerFlavour, int maxStockPerFlavour,
                 int timeBetweenShipments);
    void getShipment(int cargo[]);
};
