#include "Truck.h"
#include "VendingMachine.h"
#include "MPRNG.h"

#include <vector>

static int sum(std::vector<int> &a) {int s = 0; for(int e : a) s+=e; return s;}
void Truck::main() {
    printer.print(PrinterKind::Truck, 'S');
    VendingMachine **vendingMachines = nameServer.getMachineList();

    std::vector<int> cargo;
    cargo.resize(VendingMachine::Flavours_COUNT);

    int nextMachine = 0;

    while (true) {
        yield((mprng() % 11) + 1);
        try {
            plant.getShipment(cargo.data());
            printer.print(PrinterKind::Truck, 'P', sum(cargo));
        } catch (BottlingPlant::Shutdown) {
            break;
        }

        //At most go through all vendingMachines in one run
        for (int x = 0; x < numVendingMachines; x++) {
            printer.print(PrinterKind::Truck, 'd', nextMachine, sum(cargo));
            int *inventory = vendingMachines[nextMachine]->inventory();
            int notReplenished = 0;
            for (int ix = 0; ix < (int)cargo.size(); ix++) {
                int optimal = maxStockPerFlavour - inventory[ix];
                int transfer = std::min(optimal, cargo[ix]);
                notReplenished += optimal - transfer;
                inventory[ix] += transfer;
                cargo[ix] -= transfer;
            }
            if (notReplenished) {
                printer.print(PrinterKind::Truck, 'U', nextMachine, notReplenished);
            }
            vendingMachines[nextMachine]->restocked();
            printer.print(PrinterKind::Truck, 'D', nextMachine, sum(cargo));
            nextMachine = (nextMachine + 1) % numVendingMachines;

            //Stop if we have nothing left to add, leaving nextMachine for
            //  the next run (so distribution is fair).
            if (sum(cargo) == 0) break;
        }
    }
    printer.print(PrinterKind::Truck, 'F');
}
