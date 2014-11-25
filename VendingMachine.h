#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

_Task VendingMachine {
private:
    Printer &printer;
    NameServer &nameServer;
    int id;
    int sodaCost;
    int maxStockPerFlavour;
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
          id(id), sodaCost(codaCost), maxStockPerFlavour(maxStockPerFlavour) {}

    void buy(Flavours flavour, WATCard & card);
    int *inventory();
    void restocked();
    _Nomutex int cost();
    _Nomutex int getId();
private:
    void main();
};
