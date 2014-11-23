#include "WATCard.h"

WATCard::WATCard() : balance(0) { }
void WATCard::deposit(int amount) {
    balance += amount;
}
void WATCard::withdraw(int amount) {
    balance -= amount;
}
int WATCard::getBalance() {
    return balance;
}