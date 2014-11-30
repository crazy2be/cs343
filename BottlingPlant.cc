#include "BottlingPlant.h"
#include "Truck.h"

#include "MPRNG.h"
#include "VendingMachine.h"

static MPRNG randGen;

void BottlingPlant::getShipment(int cargo[]) {
    if (shuttingDown) {
        uRendezvousAcceptor();
        throw Shutdown();
    }
    for (int ix = 0; ix < (int)shipment.size(); ix++) {
        cargo[ix] = shipment[ix];
    }
}

void BottlingPlant::main() {
    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    shipment.resize(VendingMachine::Flavours_COUNT);

    while (true) {
        yield(timeBetweenShipments);
        for (int ix = 0; ix < (int)shipment.size(); ix++) {
            shipment[ix] = randGen(maxShippedPerFlavour + 1);
        }
        _Accept(~BottlingPlant) {
            shuttingDown = true;
            _Accept(getShipment);
            break;
        } or _Accept(getShipment);
    }
}
