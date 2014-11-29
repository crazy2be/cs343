#include "BottlingPlant.h"
#include "Truck.h"

#include "MPRNG.h"
#include "VendingMachine.h"

static MPRNG randGen;

void BottlingPlant::getShipment(int cargo[]) {
    printf("getShipment\n");
    shipmentsReady.acquire();
    printf("getShipment2\n");
    for (int ix = 0; ix < (int)shipment.size(); ix++) {
        cargo[ix] = shipment[ix];
    }
    shipmentsPickedUp.release();
    printf("Released shipmentsPickedUp %d\n", shipmentsPickedUp.counter());
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
        shipmentsReady.release();
        printf("Released shipmentsRead\n");
        shipmentsPickedUp.acquire();
        printf("BottlingPlant woke up\n");
    }
}
