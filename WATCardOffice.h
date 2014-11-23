#pragma once

#include "WATCard.h"
#include "Bank.h"
#include "Printer.h"

#include <vector>
#include <queue>

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        WATCard* card;
        int sid;
        int amount;
        //Not sure we are using this properly, it might not copy as intended
        WATCard::FWATCard result;
        Job(WATCard* card, int sid, int amount)
            : card(card), sid(sid), amount(amount) {}
    };
    _Task Courier {
    private:
        void main();
        WATCardOffice &office;
        Bank &bank;
    public:
        Courier(WATCardOffice &, Bank &);
    };

    std::vector<Courier *> couriers;
    std::queue<Job*> jobs;
    Printer &printer;
    Bank &bank;

    bool terminated;
    void terminate() { terminated = true; }

    void main();
public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice(Printer & prt, Bank & bank, int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create(int sid, int amount);
    WATCard::FWATCard transfer(int sid, int amount, WATCard * card);
    Job * requestWork();
};
