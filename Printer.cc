#include "Printer.h"
#include "debug.h"

#include <iostream>
using namespace std;

Printer::Printer(int numStudents, int numVendingMachines, int numCouriers)
        : numOfEachKind{0, 1, 1, 1, 1, 1, numStudents, numVendingMachines,
            numCouriers} {
    cout << "Parent\t" << "WATOff\t" << "Names\t" << "Truck\t" << "Plant\t";
    for (int i = 0; i < numStudents; i++) cout << "Stud" << i << "\t";
    for (int i = 0; i < numVendingMachines; i++) cout << "Mach" << i << "\t";
    for (int i = 0; i < numCouriers; i++) cout << "Cour" << i << "\t";
    cout << endl;

    int n = 5 + numStudents + numVendingMachines + numCouriers;
    for (int i = 0; i < n; i++) {
        cout << "*******" << "\t";
    }
    cout << endl;

    states.resize(n);
    reset();
}
Printer::~Printer() {
    cout << "***********************" << endl;
}
void Printer::reset() {
    for (int i = 0; i < (int)states.size(); i++) {
        states[i] = PrintState();
    }
}
int Printer::statesIndex(PrinterKind kind, int id) {
    int off = 0;
    dassert(kind < PrinterKind::NumKinds);
    for (int k = 0; k < (int)kind; k++) {
        off += numOfEachKind[k];
    }
    dassert(id >= 0);
    dassert(id < numOfEachKind[(int)kind]);
    return off + id;
}
PrinterKind Printer::kind(int statesIndex) {
    int off = 0;
    for (int k = 0; k < (int)PrinterKind::NumKinds; k++) {
        if (off + numOfEachKind[k] > statesIndex) {
            return (PrinterKind)k;
        }
        off += numOfEachKind[k];
    }
    dassert(false); // i out of range...
}
int PrintState::numVals(PrinterKind kind) {
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
            if (state.numVals(kind(i)) > 0) cout << " " << state.value1;
            if (state.numVals(kind(i)) > 1) cout << "," << state.value2;
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
    printInternal(kind, 0, statec, -1, -1);
}
void Printer::print(PrinterKind kind, int id, char statec) {
    printInternal(kind, id, statec, -1, -1);
}
void Printer::print(PrinterKind kind, char statec, int value1) {
    printInternal(kind, 0, statec, value1, -1);
}
void Printer::print(PrinterKind kind, int id, char statec, int value1) {
    printInternal(kind, id, statec, value1, -1);
}
void Printer::print(PrinterKind kind, char statec, int value1, int value2) {
    printInternal(kind, 0, statec, value1, value2);
}
void Printer::print(PrinterKind kind, int id, char statec, int value1, int value2) {
    printInternal(kind, id, statec, value1, value2);
}
