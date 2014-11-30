#ifdef TESTS

#include "UnitTests.h"

#include "Bank.h"

#include "Printer.h"
#include "debug.h"

using namespace std;

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

static void TestBank(uBaseTask& task) {
    Bank bank(1);
    {
        BankWithdraw task(bank, 0, 2);
        task.yield(10);
        bank.deposit(0, 1);
        bank.deposit(0, 1);
    }
}

static void VectorsEqual(vector<PrintState>& lhs, vector<PrintState>& rhs) {
    int ix = 0;
    while(ix < (int)min(lhs.size(), rhs.size())) {
        if(!lhs[ix].equals(rhs[ix])) {
            printf("Values not equal at %d:\n", ix);
            printf("Should be:\t\t"); lhs[ix].print();
            printf("But was:\t\t"); rhs[ix].print();
        }
        ix++;
    }
    if(ix < (int)lhs.size()) {
        printf("Missing values:\n");
    }
    while(ix < (int)lhs.size()) {
        printf("\t"); lhs[ix++].print();
    }

    if(ix < (int)rhs.size()) {
        printf("Extra values:\n");
    }
    while(ix < (int)rhs.size()) {
        printf("\t"); rhs[ix++].print();
    }
}

void RunAllTests(uBaseTask& task) {
	vector<PrintState> TestBankResults {
        PrintState(PrinterKind::BankDeposit, 0, ' ', 1), 
        PrintState(PrinterKind::BankDeposit, 0, ' ', 1),
        PrintState(PrinterKind::BankWithdraw, 0, ' ', 2)
    };
    TestBank(task);
    VectorsEqual(TestBankResults, printer.states);
}
#endif