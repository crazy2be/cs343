#ifndef TESTS
#error "You shouldn't compile UnitTests.cc without test mode on."
#endif

#include "UnitTests.h"

#include "Bank.h"
#include "Printer.h"
#include "Config.h"
#include "Main.h"
#include "MPRNG.h"
#include "debug.h"

using namespace std;


static void VectorsEqual(vector<PrintState> &lhs, vector<PrintState> &rhs) {
    int ix = 0;
    while (ix < (int)min(lhs.size(), rhs.size())) {
        if (!lhs[ix].equals(rhs[ix])) {
            printf("Values not equal at %d:\n", ix);
            printf("Should be:\t\t"); lhs[ix].print();
            printf("But was:\t\t"); rhs[ix].print();
        }
        ix++;
    }
    if (ix < (int)lhs.size()) {
        printf("Missing values:\n");
    }
    while (ix < (int)lhs.size()) {
        printf("\t"); lhs[ix++].print();
    }

    if (ix < (int)rhs.size()) {
        printf("Extra values:\n");
    }
    while (ix < (int)rhs.size()) {
        printf("\t"); rhs[ix++].print();
    }
}


_Task BankWithdraw {
public:
    Bank &bank;
    int id;
    int count;
    BankWithdraw(Bank & bank, int id, int count) : bank(bank), id(id), count(count) { }
    void main() {
        bank.withdraw(id, count);
    }
};

static void TestBank(uBaseTask &task) {
    testPrinter.states.clear();
    Bank bank(1);
    {
        BankWithdraw task(bank, 0, 2);
        task.yield(10);
        bank.deposit(0, 1);
        bank.deposit(0, 1);
    }

    vector<PrintState> TestBankResults {
        PrintState(PrinterKind::BankDeposit, 0, ' ', 1),
        PrintState(PrinterKind::BankDeposit, 0, ' ', 1),
        PrintState(PrinterKind::BankWithdraw, 0, ' ', 2)
    };
    VectorsEqual(TestBankResults, testPrinter.states);
}

void RunAllTests(uBaseTask &task) {
    TestBank(task);
}

Config genRandConfig() {
    Config config;
    config.sodaCost = mprng() % 10 + 1;
    config.numStudents = mprng() % 10 + 1;
    config.maxPurchases = mprng() % 10 + 1;
    config.numVendingMachines = mprng() % 10 + 1;
    config.maxStockPerFlavour = mprng() % 10 + 1;
    config.maxShippedPerFlavour = mprng() % 10 + 1;
    config.timeBetweenShipments = mprng() % 10 + 1;
    config.parentalDelay = mprng() % 10 + 1;
    config.numCouriers = mprng() % 10 + 1;
    return config;
}

Config defaultConfig() {
    Config c = {};
    c.sodaCost = 2;
    c.numStudents = 2;
    c.maxPurchases = 8;
    c.numVendingMachines = 3;
    c.maxStockPerFlavour = 5;
    c.maxShippedPerFlavour = 3;
    c.timeBetweenShipments = 3;
    c.parentalDelay = 2;
    c.numCouriers = 1;
    return c;
}

Config oneConfig() {
    Config c = {};
    c.sodaCost = 1;
    c.numStudents = 1;
    c.maxPurchases = 1;
    c.numVendingMachines = 1;
    c.maxStockPerFlavour = 1;
    c.maxShippedPerFlavour = 1;
    c.timeBetweenShipments = 1;
    c.parentalDelay = 1;
    c.numCouriers = 1;
    return c;
}

Config badConfig1() {
    Config c = {};
    c.sodaCost = 7;
    c.numStudents = 10;
    c.maxPurchases = 5;
    c.numVendingMachines = 10;
    c.maxStockPerFlavour = 9;
    c.maxShippedPerFlavour = 10;
    c.timeBetweenShipments = 8;
    c.parentalDelay = 4;
    c.numCouriers = 2;
    return c;
}

void uMain::main() {
//     Config config = genRandConfig();
//     Config config = oneConfig();
    for (int i = 0; i < 10000; i++) {
        Config config = genRandConfig();

        runTest(config);
        if (i % 100 == 0) {
            fprintf(stderr, "Iteration %d\n", i);
        }
    }
//     Config c = badConfig1();
//     runTest(c);
    //RunAllTests(*this);
}
