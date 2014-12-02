#include "Parent.h"
#include "MPRNG.h"

void Parent::main() {
    printer.print(PrinterKind::Parent, 'S');
    while (true) {
        _Accept(~Parent) {
            break;
        } _Else {
            yield(delay);
            int sid = mprng() % numStudents;
            int gift = (mprng() % 3) + 1; // Random number from 1 to 3.
            printer.print(PrinterKind::Parent, 'D', sid, gift);
            bank.deposit(sid, gift);
        }
    }
    printer.print(PrinterKind::Parent, 'F');
}
