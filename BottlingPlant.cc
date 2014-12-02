#include "BottlingPlant.h"
#include "Truck.h"
#include "VendingMachine.h"
#include "MPRNG.h"

static int sum(std::vector<int> &a) {int s = 0; for(int e : a) s+=e; return s;}
void BottlingPlant::getShipment(int cargo[]) {
    if (shuttingDown) {
        uRendezvousAcceptor();
        throw Shutdown();
    }
    for (int ix = 0; ix < (int)shipment.size(); ix++) {
        cargo[ix] = shipment[ix];
    }
    printer.print(PrinterKind::BottlingPlant, 'P');
}

void BottlingPlant::main() {
    printer.print(PrinterKind::BottlingPlant, 'S');
    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    shipment.resize(VendingMachine::Flavours_COUNT);

    while (true) {
        yield(timeBetweenShipments);
        for (int ix = 0; ix < (int)shipment.size(); ix++) {
            shipment[ix] = mprng() % (maxShippedPerFlavour + 1);
        }
        printer.print(PrinterKind::BottlingPlant, 'G', sum(shipment));
        _Accept(~BottlingPlant) {
            shuttingDown = true;
            _Accept(getShipment);
            break;
        } or _Accept(getShipment);
    }
    printer.print(PrinterKind::BottlingPlant, 'F');
}
