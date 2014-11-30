#include "Student.h"

#include "VendingMachine.h"
#include "WATCard.h"

#include "MPRNG.h"
#include "debug.h"

static MPRNG randGen;

//If the card is lost, we will retry until it is created, but
//  if it is lost once we will only add 5 dollars to it (cause the spec is strange)
static void transferWithRetry(WATCardOffice &office, WATCard*&card, int sid, int dollars) {
    while (true) {
        printf("transferWithRetry %d\n", sid);
        try {
            int preBalance = card->getBalance();
            //Wait for the transfer to complete, it won't change the card, so
            //  the return value doesn't really matter.
            office.transfer(sid, dollars, card)();
            dassert(card->getBalance() == preBalance + dollars);
            break;
        } catch (WATCardOffice::Lost) {
            dollars = 5;
            //Call create, but with zero dollars, and make create see this is special
            //  and just return right away.
            card = new WATCard();
        }
    }
}

void Student::main() {
    VendingMachine *machine = nameServer.getMachine(sid);

    //FREE THIS!
    WATCard *card = new WATCard();

    transferWithRetry(office, card, sid, 5);

    printf("main %d\n", sid);
    int quantity = (randGen() % (maxPurchases-1)) + 1;
    VendingMachine::Flavours flavour = (VendingMachine::Flavours)randGen(VendingMachine::Flavours_COUNT);

    while (quantity > 0) {
//         printf("Quantity %d for student %d\n", quantity, sid);
        try {
            //printf("Trying to buy %d\n", sid);
            machine->buy(flavour, *card);
            printf("Bought %d\n", sid);
            //*drinks soda*
            yield(randGen(1, 11));
            quantity--;
        } catch (VendingMachine::Stock) {
            //Try another machine
            //printf("No stock for student %d\n", sid);
            machine = nameServer.getMachine(sid);
        } catch (VendingMachine::Funds funds) {
            //printf("No funds for student %d\n", sid);
            transferWithRetry(office, card, sid, funds.cost + 5);
        }
    }
}
