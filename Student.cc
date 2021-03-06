#include "Student.h"
#include "VendingMachine.h"
#include "WATCard.h"
#include "debug.h"
#include "MPRNG.h"

// If the card is lost, we will retry until it is created, but if it is lost
// once we will only add 5 dollars to it (cause the spec is strange)
void Student::transferWithRetry(WATCard *&card, int dollars) {
    while (true) {
        try {
            int preBalance = card->getBalance();
            // Wait for the transfer to complete, it won't change the card, so
            // the return value doesn't really matter.
            office.transfer(sid, dollars, card)();
            dassert(card->getBalance() == preBalance + dollars);
            break;
        } catch (WATCardOffice::Lost) {
            printer.print(PrinterKind::Student, sid, 'L');
            dollars = 5;
            // Call create, but with zero dollars, and make create see this is
            // special and just return right away.
            card = new WATCard();
        }
    }
}

VendingMachine *Student::nextMachine() {
    VendingMachine *machine = nameServer.getMachine(sid);
    dassert(machine);
    printer.print(PrinterKind::Student, sid, 'V', machine->getId());
    return machine;
}

void Student::main() {
    int quantity = (mprng() % maxPurchases) + 1;
    VendingMachine::Flavours favourite =
        (VendingMachine::Flavours)(mprng() % VendingMachine::Flavours_COUNT);
    printer.print(PrinterKind::Student, sid, 'S', favourite, quantity);

    VendingMachine *machine = nextMachine();

    //FREE THIS!
    WATCard *card = new WATCard();

    transferWithRetry(card, 5);


    while (quantity > 0) {
        try {
            machine->buy(favourite, *card);
            printer.print(PrinterKind::Student, sid, 'B', card->getBalance());
            quantity--;
        } catch (VendingMachine::Stock) {
            // Try another machine
            machine = nextMachine();
        } catch (VendingMachine::Funds funds) {
            transferWithRetry(card, funds.cost + 5);
        }
        // *drinks soda, or maybe just sadness*
        yield((mprng() % 11) + 1);
    }

    delete card;
    printer.print(PrinterKind::Student, sid, 'F');
}
