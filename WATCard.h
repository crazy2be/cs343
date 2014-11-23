#pragma once

#include <uFuture.h>

#define dassert(arg) assert(arg)

//Not thread safe, should only be access by one thread anyway though
class WATCard {
    int balance;
    WATCard(const WATCard &) { dassert(false); } // prevent copying
    WATCard &operator=(const WATCard &) { dassert(false); }
  public:
    WATCard();
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit(int amount);
    void withdraw(int amount);
    int getBalance();
};
