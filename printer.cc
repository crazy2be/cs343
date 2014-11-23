#include "printer.h"

#include <iostream>
using namespace std;

#define dassert(arg) assert(arg)

Printer::Printer(int numStudents, int numVendingMachines, int numCouriers)
        : numStudents(numStudents), numVendingMachines(numVendingMachines),
            numCouriers(numCouriers) {
    int n = 5 + numStudents + numVendingMachines + numCouriers;
    states.resize(n);
    reset();
    cout << "Parent\t" << "WATOff\t" << "Names\t" << "Truck\t" << "Plant\t";
    for (int i = 0; i < numStudents; i++) cout << "Stud" << i << "\t";
    for (int i = 0; i < numVendingMachines; i++) cout << "Mach" << i << "\t";
    for (int i = 0; i < numCouriers; i++) cout << "Cour" << i << "\t";
    cout << endl;

    for (int i = 0; i < n; i++) {
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
int PrintState::numVals() {
    const static string NO_VALUE = "FWPLrR";
    const static string ONE_VALUE = "RPGVBS";
    const static string TWO_VALUE = "DCTNdUDSBt";
    if (NO_VALUE.find(statec) >= 0) return 0;
    else if (ONE_VALUE.find(statec) >= 0) return 1;
    else if (TWO_VALUE.find(statec) >= 0) return 2;
    else {
        dassert(statec == 'S');
        switch (kind) {
        case PrinterKind::Student: return 2;
        case PrinterKind::Vending: return 1;
        default: return 0;
        }
    }
}
void Printer::flush() {
    for (int i = 0; i < (int)states.size(); i++) {
        PrintState state = states.at(i);
        if (state.changed) {
            cout << state.statec;
            if (state.numVals() > 0) cout << " " << state.value1;
            if (state.numVals() > 1) cout << "," << state.value2;
        }
        cout << "\t";
    }
    cout << endl;
    reset();
}
void Printer::finishedFlush() {
    for (int i = 0; i < (int)states.size(); i++) {
        PrintState state = states.at(i);
        if (state.statec == 'F') cout << "F" << "\t";
        else cout << "..." << "\t";
    }
    cout << endl;
    reset();
}
int Printer::statesIndex(PrinterKind kind, int id) {
    switch (kind) {
    case PrinterKind::Parent: return 0;
    case PrinterKind::WATCardOffice: return 1;
    case PrinterKind::NameServer: return 2;
    case PrinterKind::Truck: return 3;
    case PrinterKind::BottlingPlant: return 4;
    case PrinterKind::Student: dassert(id < numStudents); return 5 + id;
    case PrinterKind::Vending:
        dassert(id < numVendingMachines); return 5 + numStudents + id;
    case PrinterKind::Courier:
        dassert(id < numCouriers); return 5 + numStudents + numVendingMachines;
    default: dassert(false);
    }
}
void Printer::printInternal(PrinterKind kind, int id, char statec,
                            int value1, int value2) {
    PrintState &state = states.at(statesIndex(kind, id));
    if (state.changed) flush();
    state.statec = statec;
    state.value1 = value1;
    state.value2 = value2;
    state.changed = true;
    if (statec == 'F') finishedFlush();
}
void Printer::print(PrinterKind kind, char statec) {
    printInternal(kind, -1, statec, -1, -1);
}
void Printer::print(PrinterKind kind, int id, char statec) {
    printInternal(kind, id, statec, -1, -1);
}
void Printer::print(PrinterKind kind, char statec, int value1) {
    printInternal(kind, -1, statec, value1, -1);
}
void Printer::print(PrinterKind kind, int id, char statec, int value1) {
    printInternal(kind, id, statec, value1, -1);
}
void Printer::print(PrinterKind kind, char statec, int value1, int value2) {
    printInternal(kind, -1, statec, value1, value2);
}
void Printer::print(PrinterKind kind, int id, char statec, int value1, int value2) {
    printInternal(kind, id, statec, value1, value2);
}
