#include "Bank.h"
#include "Parent.h"

#include <iostream>
using namespace std;


#include "Printer.h"
#include <vector>

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

static void TestBank() {
    Bank bank(1);
    {
        BankWithdraw task(bank, 0, 2);
        yield(10);
        bank.deposit(0, 1);
        bank.deposit(0, 1);
    }
}

//static void ve

void uMain::main() {
    vector<PrinterKind> TestBankResult{
        PrintState(PrinterKind::BankDeposit), 
        PrintState(PrinterKind::BankDeposit),
        PrintState(PrinterKind::BankWithdraw)
    };
    TestBank();
}
/*
#include "Config.h"
#include "Printer.h"
#include "Bank.h"
#include "Parent.h"
#include "WATCardOffice.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"

#include <iostream>

void uMain::main() {
    Config config;
    // TODO: soda.config should be argv[0]
    readConfigFile("soda.config", config);

    Printer printer(config.numStudents, config.numVendingMachines,
                    config.numCouriers);
    Bank bank(config.numStudents);
    Parent parent(printer, bank, config.numStudents, config.parentalDelay);
    WATCardOffice office(printer, bank, config.numCouriers);
    NameServer nameServer(printer, config.numVendingMachines, config.numStudents);

    std::vector<VendingMachine*> machines;
    for (int i = 0; i < config.numVendingMachines; i++) {
        VendingMachine *machine = new VendingMachine(printer, nameServer, i,
                                                     config.sodaCost,
                                                     config.maxStockPerFlavour);
        machines.push_back(machine);
    }

    {
        // We have to delete the BottlingPlant before the vending machines,
        // so we put it in it's own scope like so.
        BottlingPlant plant(printer, nameServer, config.numVendingMachines,
                            config.maxShippedPerFlavour,
                            config.maxStockPerFlavour,
                            config.timeBetweenShipments);

        std::vector<Student*> students;
        for (int i = 0; i < config.numStudents; i++) {
            Student *student = new Student(printer, nameServer, office, i,
                                           config.maxPurchases);
            students.push_back(student);
        }


        std::cout << "Created all the shit!" << std::endl;
        // loop()


        for (int i = 0; i < (int)students.size(); i++) {
            delete students[i];
        }
    }

    for (int i = 0; i < (int)machines.size(); i++) {
        delete machines[i];
    }
}
*/
