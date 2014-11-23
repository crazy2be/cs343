#pragma once

#include <vector>

_Monitor Bank {
private:
    std::vector<int> balances;
public:
    Bank(int numStudents);
    void deposit(int id, int amount);
    void withdraw(int id, int amount);
};
