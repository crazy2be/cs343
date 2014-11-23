#pragma once

#include "Printer.h"
#include "Bank.h"

_Task Parent {
    void main();
  public:
    Parent(Printer &prt, Bank &bank, int numStudents, int parentalDelay);
};
