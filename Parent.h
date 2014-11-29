#pragma once

#include "Printer.h"
#include "Bank.h"

_Task Parent {
    void main();
    Printer &printer;
    Bank &bank;
    int numStudents;
    int delay;
public:
    Parent(Printer & printer, Bank & bank, int numStudents, int delay)
        : printer(printer), bank(bank), numStudents(numStudents), delay(delay) {}
    ~Parent() {}
};
