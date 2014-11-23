#include "Printer.h"
#include "NameServer.h"
#include "CardOffice.h"

_Task Student {
    void main();
  public:
    Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
            int id, int maxPurchases);
};
