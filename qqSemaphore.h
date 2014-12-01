#pragma once

#include <queue>
#include "debug.h"

// Semaphphore-like class for use inside an monitor.
class qqSemaphore {
    int bal;
    uCondition *cond;
public:
    qqSemaphore() : bal(0), cond(new uCondition) {}
    qqSemaphore(int bal) : bal(bal), cond(new uCondition) {}
    ~qqSemaphore() { delete cond; }

    void acquire() { withdraw(1); }
    void withdraw(int amount) {
        if (bal - amount < 0) {
            cond->wait(amount);
        } else {
           bal -= amount;
        }
        dassert(bal >= 0);
    }

    void release() { deposit(1); }
    void deposit(int amount) {
        bal += amount;
        while (!cond->empty() && cond->front() <= bal) {
            bal -= amount;
            cond->signal();
        }
    }

    int counter() { return bal; }
};
