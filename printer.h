#pragma once

#include "q2tallyVotes.h"

#include <vector>

_Task Voter {
    unsigned int id;
    TallyVotes &voteTallier;
    Printer &printer;

    void main();
  public:
    enum States {Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                 Barging = 'b', Complete = 'C', Finished = 'F'};
    Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer)
        : id(id), voteTallier(voteTallier), printer(printer) {}
};

struct PrintState {
    bool changed;
    Voter::States state;
    bool vote;
    unsigned numBlocked;
    PrintState() : changed(false), state((Voter::States)'?'), vote(false), numBlocked(0) {}
};

_Monitor Printer { // or _Cormonitor
    std::vector<PrintState> states;
    void reset();
    void flush();
    void finishedFlush();
    void checkFlush(unsigned id);
  public:
    Printer(int numVoters);
    ~Printer();
    void print(unsigned id, Voter::States state);
    void print(unsigned id, Voter::States state, bool vote);
    void print(unsigned id, Voter::States state, int numBlocked);
};
