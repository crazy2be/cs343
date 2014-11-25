#include "WATCard.h"
#include "debug.h"

WATCard::WATCard() : balance(0) {}
void WATCard::deposit(int amount) {
    dassert(amount > 0);
    balance += amount;
}
void WATCard::withdraw(int amount) {
	dassert(amount > 0);
    balance -= amount;
    dassert(balance > 0);
}
int WATCard::getBalance() {
    return balance;
}
