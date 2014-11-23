#include "WATCard.h"

#define dassert(arg) assert(arg)

WATCard::WATCard() : balance(0) {}
void WATCard::deposit(int amount) {
    dassert(amount > 0);
    balance += amount;
}
void WATCard::withdraw(int amount) {
    dassert(amount > 0);
    balance -= amount;
}
int WATCard::getBalance() {
    return balance;
}
