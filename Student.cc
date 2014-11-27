#include "Student.h"

#include "VendingMachine.h"
#include "WATCard.h"

#include "debug.h"

static MPRNG randGen;

//If the card is lost, we will retry until it is created, but
//  if it is lost once we will only add 5 dollars to it (cause the spec is strange)
static void transferWithRetry(WATCardOffice &office, WATCard& *card, int sid, int dollars) {
    while (true) {
        try {
            int preBalance = card->getBalance();
            //Wait for the transfer to complete, it won't change the card, so
            //  the return value doesn't really matter.
            office.transfer(sid, dollars, card)();
            dassert(card->getBalance() == preBalance + dollars);
            break;
        } catch (WATCard::Lost) {
            dollars = 5;
            card = new WATCard();
        }
    }
}

void Student::main() {
    VendingMachine *machine = nameServer.getMachine(sid);

    //FREE THIS!
    WATCard *card = new WATCard();

    transferWithRetry(office, card, sid, 5);
    while (true) {
        int quantity = randGen(1, maxPurchases + 1);
        VendingMachine::Flavours flavour = randGen(VendingMachine::Flavours_COUNT);

        while (quantity > 0) {
            try {
                machine->buy(flavour, *card);
                //*drinks soda*
                yield(randGen(1, 11));
                quantity--;
            } catch (VendingMachine::Stock) {
                //Try another machine
                machine = nameServer.getBalance(sid);
            } catch (VendingMachine::Funds funds) {
            	transferWithRetry(office, card, sid, funds.cost + 5);
            }
        }
    }

}