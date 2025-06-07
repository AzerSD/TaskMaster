#pragma once
#include "program_config.hpp"
#include <vector>
#include <string>

class ProcessManager {
public:
    ProcessManager(const ProgramConfig& config);
    void start();
    void stop();
    void restart();
    void status() const;
    void monitor(); // Optional: Background monitoring thread
    std::vector<std::string> tokenize(const std::string& cmd);

private:
    ProgramConfig config_;
    std::vector<pid_t> pids_; // Track multiple processes
    void launchOne();
    bool isRunning(pid_t pid);
};
