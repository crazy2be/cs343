#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "CardOffice.h"

_Task Student {
private:
    Printer &printer;
    NameServer &nameServer;
    WATCardOffice &cardOffice;
    int sid;
    int maxPurchases;
public:
    Student(Printer & printer, NameServer & nameServer,
    WATCardOffice & cardOffice, int sid, int maxPurchases)
        : printer(printer), nameServer(nameServer),
        cardOffice(cardOffice), sid(sid), maxPurchases(maxPurchases) { }
private:
    void main();
};
