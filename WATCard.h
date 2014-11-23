#pragma once

class WATCard {
    WATCard(const WATCard &) // prevent copying
    WATCard &operator=(const WATCard &);
  public:
    WATCard();
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit(int amount);
    void withdraw(int amount);
    unsigned int getBalance();
};
