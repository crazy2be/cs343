#include "Bank.h"
#include "Printer.h"
#include "debug.h"

Bank::Bank(int numStudents) {
    accounts.resize(numStudents);
}
void Bank::deposit(int id, int amount) {
 	printer.print(PrinterKind::BankDeposit, id, amount);
    accounts[id].deposit(amount);
}
void Bank::withdraw(int id, int amount) {
    accounts[id].withdraw(amount);
    printer.print(PrinterKind::BankWithdraw, id, amount);
}