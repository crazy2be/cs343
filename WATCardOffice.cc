#include "WATCardOffice.h"
#include "MPRNG.h"
#include "debug.h"

MPRNG randGen;

void WATCardOffice::Courier::main() {
    while (true) {
        WATCardOffice::Job *job = office.requestWork();
        if (!job) break;
        bank.withdraw(job->sid, job->amount);
        job->card->deposit(job->amount);

        //1 in 6 chance to lose it
        if (randGen(6) == 0) {
            //Lose it
            delete job->card;
            job->result.exception(new WATCardOffice::Lost());
        } else {
            job->result.delivery(job->card);
        }
        delete job;
    }
}
WATCardOffice::Courier::Courier(WATCardOffice &office, Bank &bank)
    : office(office), bank(bank) {}


void WATCardOffice::main() { }

WATCardOffice::WATCardOffice(Printer &printer, Bank &bank, int numCouriers)
    : printer(printer), bank(bank), terminated(false) {
    for (int ix = 0; ix < numCouriers; ix++) {
        couriers.push_back(new Courier(*this, bank));
    }
}
WATCardOffice::~WATCardOffice() {
    terminate();
    for (int ix = 0; ix < (int)couriers.size(); ix++) {
        delete couriers[ix];
    }
}
WATCard::FWATCard WATCardOffice::create(int sid, int amount) {
    WATCard *card = new WATCard();

    return transfer(sid, amount, card);
}
WATCard::FWATCard WATCardOffice::transfer(int sid, int amount, WATCard *card) {
    WATCardOffice::Job *job = new WATCardOffice::Job(card, sid, amount);

    jobs.push(job);

    return job->result;
}
WATCardOffice::Job *WATCardOffice::requestWork() {
    if (jobs.empty()) {
        _Accept(create, transfer, terminated);
    }
    if (terminated) {
        dassert(jobs.empty());
        return NULL;
    }
    dassert(!jobs.empty());

    WATCardOffice::Job *job = jobs.front();
    jobs.pop();
    return job;
}
