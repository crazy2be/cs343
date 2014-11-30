#include "WATCardOffice.h"
#include "MPRNG.h"
#include "debug.h"

static MPRNG randGen;

void WATCardOffice::Courier::main() {
    while (true) {
        WATCardOffice::Job *job = office.requestWork();
        printf("Got work %p\n", job);
        if (!job) break;
        bank.withdraw(job->sid, job->amount);
        printf("Withdrew from bank\n");
        job->card->deposit(job->amount);
        printf("Deposited\n");

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
    printf("courier done\n");
}
WATCardOffice::Courier::Courier(WATCardOffice &office, Bank &bank)
    : office(office), bank(bank) {}


void WATCardOffice::main() { }

WATCardOffice::WATCardOffice(Printer &printer, Bank &bank, int numCouriers)
    : printer(printer), bank(bank) {
    for (int ix = 0; ix < numCouriers; ix++) {
        couriers.push_back(new Courier(*this, bank));
    }
}
WATCardOffice::~WATCardOffice() {
    printf("office start dtor\n");
    for (int ix = 0; ix < (int)couriers.size(); ix++) {
        delete couriers[ix];
    }
    printf("office end dtor\n");
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
        _Accept(create, transfer) {

        } or _Accept(~WATCardOffice) {
            dassert(jobs.empty());
            return NULL;
        }
    }
    dassert(!jobs.empty());

    WATCardOffice::Job *job = jobs.front();
    jobs.pop();
    return job;
}
