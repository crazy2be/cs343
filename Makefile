OPT:=-O2 -multi
F = RELEASE

CXX = u++
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -std=c++11 -D${F} ${OPT}

OBJECTS = Printer.o Config.o Soda.o Bank.o BottlingPlant.o WATCard.o WATCardOffice.o VendingMachine.o Truck.o Student.o Parent.o NameServer.o UnitTests.o
DEPENDS = ${OBJECTS:.o=.d}

.PHONY: all clean

all: soda

soda: ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@\

${OBJECTS}:

-include ${DEPENDS}

clean :
	rm -f *.d *.o soda
