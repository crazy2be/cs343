#include "q2printer.h"

#include <iostream>
using namespace std;

Printer::Printer(int numVoters) {
    states.resize(numVoters);
    reset();
    for (int i = 0; i < numVoters; i++) {
        cout << "Voter" << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < numVoters; i++) {
        cout << "=======" << "\t";
    }
    cout << endl;
}
Printer::~Printer() {
    cout << "=================" << endl;
    cout << "All tours started" << endl;
}
void Printer::reset() {
    for (int i = 0; i < (int)states.size(); i++) {
        states[i] = PrintState();
    }
}
void Printer::flush() {
    for (int i = 0; i < (int)states.size(); i++) {
        PrintState state = states.at(i);
        if (state.changed) {
            cout << (unsigned char)state.state;
            if (state.state == 'V' || state.state == 'F') {
                cout << " " << state.vote;
            } else if (state.state == 'B' || state.state == 'U') {
                cout << " " << state.numBlocked;
            }
        }
        cout << "\t";
    }
    cout << endl;
    reset();
}
void Printer::finishedFlush() {
    for (int i = 0; i < (int)states.size(); i++) {
        PrintState state = states.at(i);
        if (state.state == 'F') {
            cout << "F " << state.vote;
        } else {
            cout << "...";
        }
        cout << "\t";
    }
    cout << endl;
    reset();
}
void Printer::checkFlush(unsigned id) {
//     flush(); // TODO REMOVE
    if (states.at(id).changed) {
        flush();
    }
}
void Printer::print(unsigned id, Voter::States state) {
    checkFlush(id);
    states.at(id).state = state;
    states.at(id).changed = true;
}
void Printer::print(unsigned id, Voter::States state, bool vote) {
    checkFlush(id);
    states.at(id).state = state;
    states.at(id).vote = vote;
    states.at(id).changed = true;
    if (state == 'F') {
        finishedFlush();
    }
}
void Printer::print(unsigned id, Voter::States state, int numBlocked) {
    checkFlush(id);
    states.at(id).state = state;
    states.at(id).numBlocked = numBlocked;
    states.at(id).changed = true;
}
