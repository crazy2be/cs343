#pragma once

#include <vector>
#undef __U_SEMAPHORE_MONITOR__
#include <uSemaphore.h>

_Monitor Bank {
private:
    class qqSemaphore {
        int bal;
        uCondition *cond;
    public:
        qqSemaphore() : bal(0), cond(new uCondition) {}
        ~qqSemaphore() { delete cond; }
        void withdraw(int amount) {
            bal -= amount;
            if (bal < 0) {
                cond->wait();
                if (bal >= 0) {
                    cond->signal();
                }
            }
        }
        void deposit(int amount) {
            bal += amount;
            if (bal >= 0) {
                cond->signal();
            }
        }
    };
    std::vector<qqSemaphore> accounts;
public:
    Bank(int numStudents);
    void deposit(int id, int amount);
    //Blocks until enough money is deposited to cover the withdrawal
    void withdraw(int id, int amount);
};
