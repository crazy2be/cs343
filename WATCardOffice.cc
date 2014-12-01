#include "WATCardOffice.h"
#include "debug.h"

void WATCardOffice::Courier::main() {
    printer.print(PrinterKind::Courier, 'S');
    while (true) {
        WATCardOffice::Job *job = office.requestWork();
        if (!job) break;
        printer.print(PrinterKind::Courier, 't', job->sid, job->amount);
        bank.withdraw(job->sid, job->amount);
        job->card->deposit(job->amount);
        printer.print(PrinterKind::Courier, 'T', job->sid, job->amount);

        //1 in 6 chance to lose it
        if ((rand() % 6) == 0) {
            //Lose it
            delete job->card;
            job->result.exception(new WATCardOffice::Lost());
        } else {
            job->result.delivery(job->card);
        }
        delete job;
    }
    printer.print(PrinterKind::Courier, 'F');
    office.courierDone();
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
        jobs.push(NULL);
        jobsReady.release();
    }

    couriersDone.withdraw((int)couriers.size());

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

    WATCard::FWATCard fcard = job->result;
    jobs.push(job);
    jobsReady.release();

    printer.print(PrinterKind::WATCardOffice, 'T', sid, amount);
    
    return fcard;
}
WATCardOffice::Job *WATCardOffice::requestWork() {
    jobsReady.acquire();
    dassert(!jobs.empty());

    WATCardOffice::Job *job = jobs.front();
    jobs.pop();
    printer.print(PrinterKind::WATCardOffice, 'W');
    return job;
}
