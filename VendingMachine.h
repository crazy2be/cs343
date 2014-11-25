#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

#include "debug.h"

#include <vector>
#include <uSemaphore.h>

_Task VendingMachine {
private:
    Printer &printer;
    NameServer &nameServer;
    int id;
    int sodaCost;
    int maxStockPerFlavour;

    //Index is Flavours, value is count
    std::vector<int> sodas;
    uSemaphore sodasLock;

public:
    enum Flavours {
        Flavours_A,
        Flavours_B,
        Flavours_C,
        Flavours_D,
        Flavours_COUNT
    };                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine(Printer & printer, NameServer & nameServer,
                   int id, int sodaCost, int maxStockPerFlavour)
        : printer(printer), nameServer(nameServer),
          id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour) {
        sodas.resize(Flavours_COUNT);
        nameServer.VMregister(this);
    }

    void buy(Flavours flavour, WATCard & card);
    //Calling this requires restocked to be called sometime later,
    //  so we can block access to inventory and be thread safe.
    int *inventory(); //sodasLock.P()
    void restocked(); //sodasLock.V()
    _Nomutex int cost() {
        return sodaCost;
    }
    _Nomutex int getId() {
        return id;
    }
private:
    void main() {}
};
