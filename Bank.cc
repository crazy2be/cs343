#include "Bank.h"
#include "Printer.h"
#include "debug.h"

Bank::Bank(int numStudents) {
    accounts.resize(numStudents);
}
void Bank::deposit(int id, int amount) {
    testPrinter.print(PrinterKind::BankDeposit, id, amount);
    accounts[id].deposit(amount);
    // Not gaurenteed to be wrong, but probably wrong.
//     dassert(accounts[id].counter() < 500);
}
void Bank::withdraw(int id, int amount) {
    testPrinter.print(PrinterKind::BankWithdraw, id, amount);
    accounts[id].withdraw(amount);
}
