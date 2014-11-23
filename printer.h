#pragma once

#include <vector>


enum class PrinterKind {INVALID = 0, Parent, WATCardOffice, NameServer, Truck,
    BottlingPlant, Student, Vending, Courier, NumKinds};

struct PrintState {
    bool changed;
    char statec;
    int value1;
    int value2;
    int numVals(PrinterKind kind);
    PrintState() : changed(false), statec('?'), value1(-1), value2(-1) {}
};

_Monitor Printer { // or _Cormonitor
    std::vector<PrintState> states;
    void reset();
    void flush();
    void finishedFlush();

    int numStudents;
    int numVendingMachines;
    int numCouriers;

    int numOfEachKind[(int)PrinterKind::NumKinds];
    int statesIndex(PrinterKind kind, int id);
    PrinterKind kind(int statesIndex);

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
