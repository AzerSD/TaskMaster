#include "taskmaster.hpp"

Taskmaster::Taskmaster(const std::string& configPath)
    : configPath_(configPath), configParser_(configPath), shell_(this) {}

void Taskmaster::run() {
    loadConfig();
    setupSignalHandlers();
    shell_.start();  // Start interactive control shell
}

void Taskmaster::loadConfig() {
    // Parse config and initialize ProcessManagers
}

void Taskmaster::reloadConfig() {
    // Reload config and update process list
}

void Taskmaster::setupSignalHandlers() {
    // Use sigaction for SIGHUP etc.
}
