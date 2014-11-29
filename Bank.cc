#include "Bank.h"
#include "debug.h"

Bank::Bank(int numStudents) {
    accounts.resize(numStudents);
}
void Bank::deposit(int id, int amount) {
    printf("Bank: deposit %d in %d\n", amount, id);
    accounts[id].withdraw(amount);
}
void Bank::withdraw(int id, int amount) {
    printf("Bank: withdraw %d from %d\n", amount, id);
    accounts[id].deposit(amount);
}
