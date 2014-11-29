#include "Parent.h"

#include "MPRNG.h"

static MPRNG randGen;

void Parent::main() {
    while (true) {
        _Accept(~Parent) {
            break;
        } _Else { }

        yield(delay);
        int gift = randGen(1, 4); //Random number from 1 to 3.
        int sid = randGen(numStudents);
       // printf("Parent: about to deposit %d to %d\n", gift, sid);
        bank.deposit(sid, gift);
        //printf("Parent: deposited %d in %d\n", gift, sid);
    }
}
