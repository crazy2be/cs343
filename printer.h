#pragma once

#include <vector>


enum class PrinterKind {INVALID, Parent, WATCardOffice, NameServer, Truck,
    BottlingPlant, Student, Vending, Courier};

struct PrintState {
    bool changed;
    PrinterKind kind;
    char statec;
    int value1;
    int value2;
    int numVals();
    PrintState() : changed(false), kind(PrinterKind::INVALID), statec('?'),
        value1(-1), value2(-1) {}
};

_Monitor Printer { // or _Cormonitor
    std::vector<PrintState> states;
    int numStudents;
    int numVendingMachines;
    int numCouriers;
    void reset();
    void flush();
    void finishedFlush();
    int statesIndex(PrinterKind kind, int id);
    void printInternal(PrinterKind kind, int id, char statec, int value1, int value2);
  public:
    Printer(int numStudents, int numVendingMachines, int numCouriers);
    ~Printer();
    void print(PrinterKind kind, char state);
    void print(PrinterKind kind, char state, int value1);
    void print(PrinterKind kind, char state, int value1, int value2);
    void print(PrinterKind kind, int id, char state);
    void print(PrinterKind kind, int id, char state, int value1);
    void print(PrinterKind kind, int id, char state, int value1, int value2);
};
