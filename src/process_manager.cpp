#include "process_manager.hpp"

ProcessManager::ProcessManager(const ProgramConfig& config)
    : config_(config) {}

void ProcessManager::start() {
    // Fork and exec config_.numProcs processes
}

void ProcessManager::stop() {
    // Send stop signal and kill if timeout
}

void ProcessManager::restart() {
    stop();
    start();
}

void ProcessManager::status() const {
    // Print status for each pid
}
