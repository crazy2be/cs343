#include "Bank.h"
#include "Printer.h"
#include "debug.h"

Bank::Bank(int numStudents) {
    accounts.resize(numStudents);
}
void Bank::deposit(int id, int amount) {
    testPrinter.print(PrinterKind::BankDeposit, id, amount);
    accounts[id].deposit(amount);
}
void Bank::withdraw(int id, int amount) {
    accounts[id].withdraw(amount);
    testPrinter.print(PrinterKind::BankWithdraw, id, amount);
}
