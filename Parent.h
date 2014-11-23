#pragma once

#include "Printer.h"
#include "Bank.h"

_Task Parent {
    void main();
    Printer &printer;
    Bank &bank;
    int students;
    int delay;
public:
    Parent(Printer & printer, Bank & bank, int students, int delay)
        : printer(printer), bank(bank), students(students), delay(delay) {}
    ~Parent() {}
};
