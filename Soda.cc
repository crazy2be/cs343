#include "Config.h"
#include "Main.h"

void argErr(char *argv0) {
    std::cerr << "Usage: " << argv0 << " [ config-file [ random-seed (> 0) ] ]"
        << std::endl;
    exit(1);
}

void uMain::main() {
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
