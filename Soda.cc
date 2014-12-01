#include "Config.h"
#include "Main.h"

#include <iostream>

void argErr(char *argv0) {
    std::cerr << "Usage: " << argv0 << " [ config-file [ random-seed (> 0) ] ]"
        << std::endl;
    exit(1);
}

void p(const char* line) {
    printf("%s\n", line);
}

void run(int cost, int students, int purchases, int machines, int stock, 
    int shipSize, int shipTime, int parentDelay, int couriers) {
    Config config;
    config.sodaCost = cost;
    config.numStudents = students;
    config.maxPurchases = purchases;
    config.numVendingMachines = machines;
    config.maxStockPerFlavour = stock;
    config.maxShippedPerFlavour = shipSize;
    config.timeBetweenShipments = shipTime;
    config.parentalDelay = parentDelay;
    config.numCouriers = couriers;

    srand(2340872340);
    runTest(config);
}

void testdocs() {
    p("Simplest possible test case");
    //cost, students, purchases, machines, stock, shipSize, shipTime, parentDelay, couriers
    run(1,     1,         1,        1,      1,        1,       1,          1,          1);

    p("Default config");
    //cost, students, purchases, machines, stock, shipSize, shipTime, parentDelay, couriers
    run(2,     2,         8,        3,      5,        3,       3,          2,          1);

    p("Multiple couriers");
    //cost, students, purchases, machines, stock, shipSize, shipTime, parentDelay, couriers
    run(2,     2,         8,        3,      5,        3,       3,          2,          1);

    p("More students than vending machines (so they have to use round-robin)");
    //cost, students, purchases, machines, stock, shipSize, shipTime, parentDelay, couriers
    run(2,     2,         8,        3,      5,        3,       3,          2,          1);

    p("Shipping and buying a lot, but with a machine that only holds a little");
    //cost, students, purchases, machines, stock, shipSize, shipTime, parentDelay, couriers
    run(1,     1,         10,        1,      1,        10,       1,          1,          1);
}

void uMain::main() {
    testdocs();
    return;

    std::string configName = "soda.config";
    int seed = getpid();
    switch (argc) {
    case 3: seed = atoi(argv[2]);
    case 2: configName = argv[1];
    case 1: break;
    default: argErr(argv[0]);
    }
    if (seed < 0) argErr(argv[0]);

    Config config;
    readConfigFile(configName.c_str(), config);
    srand(seed);

    Main(config);
}
