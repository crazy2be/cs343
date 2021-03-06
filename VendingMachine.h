#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

#include "qqSemaphore.h"
#include "debug.h"

#include <vector>

_Task VendingMachine {
private:
    Printer &printer;
    NameServer &nameServer;
    int id;
    int sodaCost;
    int maxStockPerFlavour;

    //Index is Flavours, value is count
    std::vector<int> sodas;
    qqSemaphore sodasLock;

public:
    enum Flavours {
        Flavours_A,
        Flavours_B,
        Flavours_C,
        Flavours_D,
        Flavours_COUNT
    };                 // flavours of soda (YOU DEFINE)
    _Event Funds {
    public:
        int cost;
        Funds(int cost) : cost(cost) { }
    };                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine(Printer & printer, NameServer & nameServer,
                   int id, int sodaCost, int maxStockPerFlavour)
            : printer(printer), nameServer(nameServer), id(id),
            sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour),
            sodasLock(1) {
        printer.print(PrinterKind::VendingMachine, id, 'S', sodaCost);
        sodas.resize(Flavours_COUNT);
        nameServer.VMregister(this);
    }
    ~VendingMachine() { printer.print(PrinterKind::VendingMachine, id, 'F'); }

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
