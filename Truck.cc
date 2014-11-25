#include <vector>

#include "MPRNG.h"

#include "Truck.h"
#include "VendingMachine.h"

static MPRNG randGen;

Truck::Truck(Printer &printer, NameServer &nameServer, BottlingPlant &plant,
             int numVendingMachines, int maxStockPerFlavour)
    : printer(printer), nameServer(nameServer), plant(plant),
      numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {

}

void Truck::main() {
    VendingMachine **vendingMachines = nameServer.getMachineList();

    std::vector<int> cargo;
    cargo.resize(VendingMachine::Flavours_COUNT);

    int nextMachine = 0;

    while (true) {
        yield(randGen(1, 10));
        try {
            plant.getShipment(cargo.data());
        } catch (BottlingPlant::Shutdown) {
            break;
        }

        //At most go through all vendingMachines in one run
        for (int x = 0; x < numVendingMachines; x++) {
            int *inventory = vendingMachines[nextMachine]->inventory();
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
            nextMachine = (nextMachine + 1) % numVendingMachines;

            //Stop if we have nothing left to add, leaving nextMachine for
            //  the next run (so distribution is fair).
            if (cargoZeros == (int)cargo.size()) break;
        }
    }
}