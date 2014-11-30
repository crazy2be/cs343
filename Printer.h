#pragma once

#include <vector>


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

    //TESTS print statements, ignored by the regular printed, but
    //  used by the TESTS printer.    
    , BankDeposit
    , BankWithdraw
    
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
        
    void print();
    bool equals(PrintState& other) {
        return kind==other.kind
        && id==other.id
        && statec==other.statec 
        && value1 == other.value1 
        && value2 == other.value2;
    }
};

_Monitor Printer { // or _Cormonitor
    #ifdef TESTS
public:
    #endif
    std::vector<PrintState> states;
    int numOfEachKind[(int)PrinterKind::NumKinds];
    bool tests;

    void reset();
    void flush();
    void finishedFlush();

    int statesIndex(PrinterKind kind, int id);
    PrinterKind kind(int statesIndex);

    void printInternal(PrinterKind kind, int id, char statec, int value1, int value2);
  public:

    Printer();
    Printer(int numStudents, int numVendingMachines, int numCouriers);

    ~Printer();
    void print(PrinterKind kind, char state);
    void print(PrinterKind kind, char state, int value1);
    void print(PrinterKind kind, char state, int value1, int value2);
    void print(PrinterKind kind, int id, char state);
    void print(PrinterKind kind, int id, char state, int value1);
    void print(PrinterKind kind, int id, char state, int value1, int value2);
    void print(PrinterKind kind, int id=0, int value1=-1, int value=-1);
};

extern Printer printer;
