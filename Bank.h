#pragma once

#include <vector>
#include <queue>

_Monitor Bank {
private:
    class qqSemaphore {
        int bal;
        std::queue<int> bals;
        uCondition *cond;
    public:
        qqSemaphore() : bal(0), cond(new uCondition) {}
        ~qqSemaphore() { delete cond; }
        void withdraw(int amount) {
            if (bal - amount < 0) {
                bals.push(amount);
                cond->wait();
            }
            bal -= amount;
        }
        void deposit(int amount) {
            bal += amount;
            while (!cond->empty() && bals.front() < bal) {
                cond->signalBlock();
            }
        }
    };
    std::vector<qqSemaphore> accounts;
public:
    Bank(int numStudents);
    void deposit(int id, int amount);
    void withdraw(int id, int amount);
};
