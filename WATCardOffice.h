#pragma once

#include <WATCard.h>

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job(Args args) : args(args) {}
    };
    _Task Courier { ... };                 // communicates with bank

    void main();
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create(int sid, int amount);
    WATCard::FWATCard transfer(int sid, int amount, WATCard *card);
    Job *requestWork();
};
