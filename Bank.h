#pragma once

#include "qqSemaphore.h"

#include <vector>
#include <queue>

_Monitor Bank {
private:
    std::vector<qqSemaphore> accounts;
public:
    Bank(int numStudents);
    void deposit(int id, int amount);
    //Blocks until enough money is deposited to cover the withdrawal
    void withdraw(int id, int amount);
};
