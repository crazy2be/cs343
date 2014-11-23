#pragma once

#include <vector>
#include <uSemaphore.h>

_Monitor Bank {
private:
    std::vector<uSemaphore*> balances;
public:
    Bank(int numStudents);
    ~Bank();
    void deposit(int id, int amount);
    void withdraw(int id, int amount);
};
