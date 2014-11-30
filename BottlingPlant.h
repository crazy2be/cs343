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
    bool shuttingDown;

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
            timeBetweenShipments(timeBetweenShipments),
            shuttingDown(false) {}
    virtual ~BottlingPlant();

    void getShipment(int cargo[]);
private:
    _Mutex void main();
};
