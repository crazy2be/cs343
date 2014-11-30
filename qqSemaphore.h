#pragma once

#include <queue>
#include "debug.h"

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
            bals.push(amount);
            cond->wait();
        }
        bal -= amount;
        dassert(bal >= 0);
    }

    void release() { deposit(1); }
    void deposit(int amount) {
        bal += amount;
        while (!cond->empty() && bals.front() <= bal) {
            cond->signalBlock();
        }
    }

    int counter() { return bal; }
};
