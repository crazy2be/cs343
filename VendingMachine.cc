#include "VendingMachine.h"

void VendingMachine::buy(Flavours flavour, WATCard &card) {
    sodasLock.acquire();
    int &stock = sodas[flavour];
    dassert(stock >= 0);
    if (stock <= 0) {
        sodasLock.release();
        //Ugh... I will move this to the main later... it is really pointless
        //  to do this on another thread if we aren't yielding though...
        throw Stock();
    }

    if (card.getBalance() < sodaCost) {
        sodasLock.release();
        throw Funds(sodaCost);
    }

    //The buy was successful
    card.withdraw(sodaCost);
    stock--;
    sodasLock.release();
}

int *VendingMachine::inventory() {
    sodasLock.acquire();
    return sodas.data();
}

void VendingMachine::restocked() {
    dassert(sodasLock.counter() == 0);
    sodasLock.release();
}
