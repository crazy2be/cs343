#pragma once

#include "Printer.h"
#include "Bank.h"

_Task Parent {
    void main();
    Printer &printer;
    Bank &bank;
    int numStudents;
    int parentalDelay;
    bool terminated;
public:
    Parent(Printer & printer, Bank & bank, int numStudents, int parentalDelay)
        : printer(printer), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay), terminated(false) {}
    ~Parent();
};
