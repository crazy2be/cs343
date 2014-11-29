#include "Bank.h"
#include "debug.h"

Bank::Bank(int numStudents) {
    accounts.resize(numStudents);
}
void Bank::deposit(int id, int amount) {
    accounts[id].deposit(amount);
}
void Bank::withdraw(int id, int amount) {
    accounts[id].withdraw(amount);
}
