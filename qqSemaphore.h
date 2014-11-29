#pragma once

#include <queue>

// Semaphphore-like class for use inside an monitor.
class qqSemaphore {
    int bal;
    std::queue<int> bals;
    uCondition *cond;
public:
    qqSemaphore() : bal(0), cond(new uCondition) {}
    qqSemaphore(int bal) : bal(bal), cond(new uCondition) {}
    ~qqSemaphore() { delete cond; }

    void acquire() { withdraw(1); }
    void withdraw(int amount) {
        if (bal - amount < 0) {
            printf("Blockde on qqSemaphore\n");
            bals.push(amount);
            cond->wait();
        }
        bal -= amount;
    }

    void release() { deposit(1); }
    void deposit(int amount) {
        bal += amount;
        while (!cond->empty() && bals.front() <= bal) {
         //   printf("Signalling because %d < %d\n", bals.front(), bal);
            cond->signalBlock();
        }
       // printf("Deposited %d. Balance %d\n", amount, bal);
    }

    int counter() { return bal; }
};
