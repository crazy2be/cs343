#include "Truck.h"
#include "VendingMachine.h"

#include "MPRNG.h"

#include <vector>

static MPRNG randGen;

void Truck::main() {
    VendingMachine **vendingMachines = nameServer.getMachineList();

    std::vector<int> cargo;
    cargo.resize(VendingMachine::Flavours_COUNT);

    int nextMachine = 0;

    while (true) {
        yield(randGen(1, 11));
        try {
            plant.getShipment(cargo.data());
        } catch (BottlingPlant::Shutdown) {
            break;
        }

        //At most go through all vendingMachines in one run
        for (int x = 0; x < numVendingMachines; x++) {
            printf("Restocking %d\n", x);
            int *inventory = vendingMachines[nextMachine]->inventory();
            printf("Got inventory %d\n", x);
            int cargoZeros = 0;
            for (int ix = 0; ix < (int)cargo.size(); ix++) {
                int transfer = std::min(maxStockPerFlavour - inventory[ix], //Fill it up
                                   cargo[ix]); //Or at least add as many as we can
                inventory[ix] += transfer;
                cargo[ix] -= transfer;
                if (cargo[ix] == 0) {
                    cargoZeros++;
                }
            }
            printf("About to restock %d\n", x);
            vendingMachines[nextMachine]->restocked();
            printf("Restocked %d\n", x);
            nextMachine = (nextMachine + 1) % numVendingMachines;

            //Stop if we have nothing left to add, leaving nextMachine for
            //  the next run (so distribution is fair).
            if (cargoZeros == (int)cargo.size()) break;
        }
    }
}
