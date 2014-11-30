#ifndef TESTS
#error "You shouldn't compile UnitTests.cc without test mode on."
#endif

#include "UnitTests.h"

#include "Bank.h"

#include "Printer.h"
#include "debug.h"

#include "Config.h"
#include "Main.h"

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
    config.sodaCost = rand() % 10 + 1;
    config.numStudents = rand() % 10 + 1;
    config.maxPurchases = rand() % 10 + 1;
    config.numVendingMachines = rand() % 10 + 1;
    config.maxStockPerFlavour = rand() % 10 + 1;
    config.maxShippedPerFlavour = rand() % 10 + 1;
    config.timeBetweenShipments = rand() % 10 + 1;
    config.parentalDelay = rand() % 10 + 1;
    config.numCouriers = rand() % 10 + 1;
    return config;
}

void uMain::main() {
    Config config = genRandConfig();

    printf(
        "sodaCost %d, "
        "numStudents %d, "
        "maxPurchases %d, "
        "numVendingMachines %d, "
        "maxStockPerFlavour %d, "
        "maxShippedPerFlavour %d, "
        "timeBetweenShipments %d, "
        "parentalDelay %d, "
        "numCouriers %d\n",
        config.sodaCost,
        config.numStudents,
        config.maxPurchases,
        config.numVendingMachines,
        config.maxStockPerFlavour,
        config.maxShippedPerFlavour,
        config.timeBetweenShipments,
        config.parentalDelay,
        config.numCouriers
    );

    Main(config);
    //RunAllTests(*this);
}
