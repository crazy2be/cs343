#pragma once

#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"

class VendingMachine;

_Task Student {
private:
    Printer &printer;
    NameServer &nameServer;
    WATCardOffice &office;
    int sid;
    int maxPurchases;
public:
    Student(Printer & printer, NameServer & nameServer, WATCardOffice & office,
            int sid, int maxPurchases)
        : printer(printer), nameServer(nameServer), office(office), sid(sid),
            maxPurchases(maxPurchases) { }
private:
    void main();
    VendingMachine *nextMachine();
};
