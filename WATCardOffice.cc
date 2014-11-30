#include "WATCardOffice.h"
#include "MPRNG.h"
#include "debug.h"

static MPRNG randGen;

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

WATCardOffice::WATCardOffice(Printer &printer, Bank &bank, int numCouriers)
        : printer(printer), bank(bank) {
    for (int ix = 0; ix < numCouriers; ix++) {
        couriers.push_back(new Courier(printer, *this, bank));
    }
    printer.print(PrinterKind::WATCardOffice, 'S');
}
WATCardOffice::~WATCardOffice() {
    for (int ix = 0; ix < (int)couriers.size(); ix++) {
        delete couriers[ix];
    }
    printer.print(PrinterKind::WATCardOffice, 'F');
}
WATCard::FWATCard WATCardOffice::create(int sid, int amount) {
    WATCard *card = new WATCard();

    auto result = transfer(sid, amount, card);
    printer.print(PrinterKind::WATCardOffice, 'C', sid, amount);
    return result;
}
WATCard::FWATCard WATCardOffice::transfer(int sid, int amount, WATCard *card) {
    WATCardOffice::Job *job = new WATCardOffice::Job(card, sid, amount);

    jobs.push(job);
    printer.print(PrinterKind::WATCardOffice, 'T', sid, amount);
    return job->result;
}
WATCardOffice::Job *WATCardOffice::requestWork() {
    if (jobs.empty()) {
        _Accept(~WATCardOffice) {
            dassert(jobs.empty());
            printer.print(PrinterKind::WATCardOffice, 'W');
            return NULL;
        } or _Accept(create, transfer) {}
    }
    dassert(!jobs.empty());

    WATCardOffice::Job *job = jobs.front();
    jobs.pop();
    printer.print(PrinterKind::WATCardOffice, 'W');
    return job;
}
