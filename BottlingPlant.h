#pragma once

#include <uSemaphore.h>

#include "Printer.h"
#include "NameServer.h"

#include <vector>

_Task BottlingPlant {
private:
    Printer &printer;
    NameServer &nameServer;
    int numVendingMachines;
    int maxShippedPerFlavour;
    int maxStockPerFlavour;
    int timeBetweenShipments;

    uSemaphore shipmentsReady;
    uSemaphore shipmentsPickedUp;
    std::vector<int> shipment;

public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant(Printer & printer, NameServer & nameServer, int numVendingMachines,
                  int maxShippedPerFlavour, int maxStockPerFlavour, int timeBetweenShipments)
        : printer(printer), nameServer(nameServer), numVendingMachines(numVendingMachines),
          maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour),
          timeBetweenShipments(timeBetweenShipments) {
        //Start at no shipmentsReady
        shipmentsReady.P();
        shipmentsPickedUp.P();
    }

    void getShipment(int cargo[]);
private:
    void main();
};
