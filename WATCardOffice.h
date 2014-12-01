#pragma once

#include "WATCard.h"
#include "Bank.h"
#include "Printer.h"

#include "qqSemaphore.h"

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
        Printer &printer;
        WATCardOffice &office;
        Bank &bank;
    public:
        Courier(Printer &printer, WATCardOffice &office, Bank &bank)
            : printer(printer), office(office), bank(bank) {}
    };

    qqSemaphore couriersDone;
public:
    void courierDone(){
        printf("before %d couriers done\n", couriersDone.counter());
        couriersDone.release();
        printf("after %d couriers done\n", couriersDone.counter());
    }

private:
    std::vector<Courier*> couriers;
    std::queue<Job*> jobs;
    qqSemaphore jobsReady;

    Printer &printer;
    Bank &bank;

    void main() {}
public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice(Printer &printer, Bank &bank, int numCouriers);
    virtual ~WATCardOffice();
    WATCard::FWATCard create(int sid, int amount);
    WATCard::FWATCard transfer(int sid, int amount, WATCard * card);
    Job * requestWork();
};
