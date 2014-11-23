#include "Bank.h"

Bank::Bank(int numStudents) {
    balances.resize(numStudents, 0);
}
void Bank::deposit(int id, int amount) {
    balances[id] += amount;
}
void Bank::withdraw(int id, int amount) {
    balances[id] -= amount;
}