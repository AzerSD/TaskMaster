#include "config_parser.hpp"
#include "process_manager.hpp"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    std::string configPath = "../config/taskmaster.yml";
    if (argc > 1) configPath = argv[1];

    try {
        ConfigParser parser(configPath);
        auto programConfigs = parser.parse();

        for (const auto& [name, config] : programConfigs) {
            std::shared_ptr<ProcessManager> pm = std::make_shared<ProcessManager>(config);

            std::cout << "Loaded Program: " << config.name << "\n";
            std::cout << "  CMD: " << config.cmd << "\n";
            std::cout << "  Num Procs: " << config.numProcs << "\n";
            std::cout << "  Autostart: " << std::boolalpha << config.autostart << "\n";
            std::cout << "  Autorestart: " << config.autorestart << "\n";
            std::cout << "  Exit codes: ";
            for (auto ec : config.exitcodes) std::cout << ec << " ";
            std::cout << "\n";
            std::cout << "  Start time: " << config.startTime << "s\n";
            std::cout << "  Start retries: " << config.startRetries << "\n";
            std::cout << "  Stop signal: " << config.stopSignal << "\n";
            std::cout << "  Stop time: " << config.stopTime << "s\n";
            std::cout << "  stdout: " << config.stdoutPath << "\n";
            std::cout << "  stderr: " << config.stderrPath << "\n";
            std::cout << "  Working dir: " << config.workingDir << "\n";
            std::cout << "  Umask: " << config.umask << "\n";
            std::cout << "  Env:\n";
            for (const auto& [k, v] : config.env) {
                std::cout << "    " << k << "=" << v << "\n";
            }
            std::cout << "---------------------------\n";
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
