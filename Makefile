OPT:=-O2 -multi

CXX = u++
BASEFLAGS = -g -Wall -Wno-unused-label -MMD -std=c++11 ${OPT}

OBJECTS = Printer.o Config.o Bank.o BottlingPlant.o WATCard.o WATCardOffice.o VendingMachine.o Truck.o Student.o Parent.o NameServer.o
DEPENDS = ${OBJECTS:.o=.d}

ifeq (${MAKECMDGOALS},tests)
$(info Making tests, not regular. Make sure you cleaned before this.)
CXXFLAGS = -DTESTS ${BASEFLAGS}
else
CXXFLAGS = ${BASEFLAGS}
endif


.PHONY: all clean

all: soda

soda: ${OBJECTS} Soda.o
	${CXX} ${CXXFLAGS} $^ -o $@\

tests: ${OBJECTS} UnitTests.o
	${CXX} ${CXXFLAGS} $^ -o $@\

${OBJECTS}:

-include ${DEPENDS} Soda.d UnitTests.d

clean:
	rm -f *.d *.o soda
