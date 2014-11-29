#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "qqSemaphore.h"

#include <vector>

_Task BottlingPlant {
private:
    Printer &printer;
    NameServer &nameServer;
    int numVendingMachines;
    int maxShippedPerFlavour;
    int maxStockPerFlavour;
    int timeBetweenShipments;

    qqSemaphore shipmentsReady;
    qqSemaphore shipmentsPickedUp;
    std::vector<int> shipment;

public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant(Printer & printer, NameServer & nameServer,
                  int numVendingMachines, int maxShippedPerFlavour,
                  int maxStockPerFlavour, int timeBetweenShipments)
        : printer(printer), nameServer(nameServer),
            numVendingMachines(numVendingMachines),
            maxShippedPerFlavour(maxShippedPerFlavour),
            maxStockPerFlavour(maxStockPerFlavour),
            timeBetweenShipments(timeBetweenShipments) {}

    void getShipment(int cargo[]);
private:
    void main();
};
