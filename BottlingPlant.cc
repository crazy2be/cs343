#include "BottlingPlant.h"
#include "Truck.h"

#include "MPRNG.h"
#include "VendingMachine.h"

static MPRNG randGen;

void BottlingPlant::getShipment(int cargo[]) {
    shipmentsReady.P();
    for (int ix = 0; ix < (int)shipment.size(); ix++) {
        cargo[ix] = shipment[ix];
    }
    shipmentsPickedUp.V();
}

void BottlingPlant::main() {
    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    shipment.resize(VendingMachine::Flavours_COUNT);

    while (true) {
        yield(timeBetweenShipments);
        for (int ix = 0; ix < (int)shipment.size(); ix++) {
            shipment[ix] = randGen(maxShippedPerFlavour + 1);
        }
        shipmentsReady.V();
        shipmentsPickedUp.P();
    }
}