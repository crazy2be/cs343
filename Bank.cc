#include "Bank.h"
#include "debug.h"

Bank::Bank(int numStudents) {
    balances.resize(numStudents);
    for (int ix = 0; ix < numStudents; ix++) {
        balances[ix] = new uSemaphore(0);
    }
}
Bank::~Bank() {
    for (int ix = 0; ix < (int)balances.size(); ix++) {
        delete balances[ix];
    }
}
void Bank::deposit(int id, int amount) {
    balances[id]->V(amount);
}
void Bank::withdraw(int id, int amount) {
    for (int ix = 0; ix < amount; ix++) {
        balances[id]->P();
    }
}
