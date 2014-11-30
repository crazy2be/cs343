#include "BottlingPlant.h"
#include "Truck.h"

#include "MPRNG.h"
#include "VendingMachine.h"

static MPRNG randGen;

BottlingPlant::~BottlingPlant() {
    printf("Destruction BottlingPlant\n");
}

void BottlingPlant::getShipment(int cargo[]) {
    printf("getShipment\n");
    if (shuttingDown) {
        uRendezvousAcceptor();
        throw Shutdown();
    }
    for (int ix = 0; ix < (int)shipment.size(); ix++) {
        cargo[ix] = shipment[ix];
    }
}

void BottlingPlant::main() {
    printf("BottlingPlant::main\n");
    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    shipment.resize(VendingMachine::Flavours_COUNT);

    while (true) {
        yield(timeBetweenShipments);
        printf("BottlingPlant preparing shipments\n");
        for (int ix = 0; ix < (int)shipment.size(); ix++) {
            shipment[ix] = randGen(maxShippedPerFlavour + 1);
        }
        _Accept(~BottlingPlant) {
            printf("BottlingPlant woke up\n");
            shuttingDown = true;
            _Accept(getShipment);
            break;
        } or _Accept(getShipment) {
            printf("Released shipmentsRead\n");
        }
    }
    printf("BottelingPlant exiting\n");
}
