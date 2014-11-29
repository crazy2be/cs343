#include "Bank.h"
#include "Parent.h"

#include <iostream>
using namespace std;

_Task BankWithdraw {
public:
	Bank& bank;
	int id;
	int count;
	BankWithdraw(Bank& bank, int id, int count) : bank(bank), id(id), count(count) { }
	void main() {
		cout << "Waiting for withdrawl" << endl;
		bank.withdraw(id, count);
		cout << "withdrawn" << endl;
	}
};

void uMain::main() {
	Bank bank(1);
	{
		BankWithdraw task(bank, 0, 2);
		yield(10);
		bank.deposit(0, 1);
		bank.deposit(0, 1);
	}
}
