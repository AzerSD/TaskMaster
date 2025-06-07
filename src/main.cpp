#include "config_parser.hpp"
#include "process_manager.hpp"
#include <iostream>
#include <memory>
#include <thread>       // For sleep_for()

int main(int argc, char* argv[]) {
    std::string configPath = "../config/taskmaster.yml";
    if (argc > 1) configPath = argv[1];

    auto configs = ConfigParser(configPath).parse();

    for (const auto &[name, cfg] : configs) {
        if (cfg.autostart) {
            std::cout << "Starting program: " << name << std::endl;
            ProcessManager pm(cfg);
            pm.start();

            std::this_thread::sleep_for(std::chrono::seconds(2));
            pm.status();

            pm.stop();
            pm.status();
        }
    }

    return 0;
}
