#pragma once

#include <vector>

#define TESTS


enum class PrinterKind {
    INVALID = 0, 
    Parent, 
    WATCardOffice, 
    NameServer, 
    Truck,
    BottlingPlant, 
    Student, 
    Vending, 
    Courier, 
    NumKinds

    #ifdef TESTS
    , BankDeposit
    , BankWithdraw
    #endif
};

struct PrintState {
    bool changed;
    PrinterKind kind;
    int id;
    char statec;
    int value1;
    int value2;
    int numVals(PrinterKind kind);
    PrintState() : changed(false), statec('?'), value1(-1), value2(-1) {}
    PrintState(PrinterKind kind, int id=0, char statec=' ', int value1=-1, int value2=-1) 
        : kind(kind), id(id), statec(statec), value1(value1), value2(value2) { }
#ifdef TESTS
        void print();
        bool equals(PrintState& other) {
            return kind==other.kind
            && id==other.id
            && statec==other.statec 
            && value1 == other.value1 
            && value2 == other.value2;
        }
#endif
};

_Monitor Printer { // or _Cormonitor
    #ifdef TESTS
public:
    #endif
    std::vector<PrintState> states;
    void reset();
    void flush();
    void finishedFlush();

    int numOfEachKind[(int)PrinterKind::NumKinds];
    int statesIndex(PrinterKind kind, int id);
    PrinterKind kind(int statesIndex);

    void printInternal(PrinterKind kind, int id, char statec, int value1, int value2);
  public:
    #ifdef TESTS
        Printer();
    #else
        Printer(int numStudents, int numVendingMachines, int numCouriers);
    #endif
    ~Printer();
    void print(PrinterKind kind, char state);
    void print(PrinterKind kind, char state, int value1);
    void print(PrinterKind kind, char state, int value1, int value2);
    void print(PrinterKind kind, int id, char state);
    void print(PrinterKind kind, int id, char state, int value1);
    void print(PrinterKind kind, int id, char state, int value1, int value2);
    #ifdef TESTS
    void print(PrinterKind kind, int id=0, int value1=-1, int value=-1);
    #endif
};

#ifdef TESTS
extern Printer printer;
#endif