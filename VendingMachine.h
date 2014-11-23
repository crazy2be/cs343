#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

_Task VendingMachine {
    void main();
  public:
    enum Flavours { ... };                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine(Printer &prt, NameServer &nameServer, int id, int sodaCost,
                   int maxStockPerFlavour);
    void buy(Flavours flavour, WATCard &card);
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};
