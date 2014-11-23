#pragma once

_Monitor Bank {
  public:
    Bank(int numStudents);
    void deposit(int id, int amount);
    void withdraw(int id, int amount);
};
