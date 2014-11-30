#include "Config.h"
#include "Main.h"

void uMain::main() {
    Config config;
    // TODO: soda.config should be argv[0]
    readConfigFile("soda.config", config);

    Main(config);
}
