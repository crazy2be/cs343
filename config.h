#pragma once

struct ConfigParms {
    int sodaCost;             // MSRP per bottle
    int numStudents;          // number of students to create
    int maxPurchases;         // maximum number of bottles a student purchases
    int numVendingMachines;   // number of vending machines
    int maxStockPerFlavour;   // maximum number of bottles of each flavour stocked
    int maxShippedPerFlavour; // number of bottles of each flavour in a shipment
    int timeBetweenShipments; // length of time between shipment pickup
    int parentalDelay;        // length of time between cash deposits
    int numCouriers;          // number of couriers in the pool
};

void readConfigFile(const char *configFile, ConfigParms &cparms);
