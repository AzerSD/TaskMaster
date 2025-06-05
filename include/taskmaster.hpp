#pragma once
#include "config_parser.hpp"
#include "process_manager.hpp"
#include "shell.hpp"
#include <map>
#include <memory>

class Taskmaster {
public:
    Taskmaster(const std::string& configPath);
    void run();

private:
    void loadConfig();
    void reloadConfig();
    void setupSignalHandlers();
    static void handleSignal(int signal);

    std::string configPath_;
    ConfigParser configParser_;
    std::map<std::string, std::shared_ptr<ProcessManager>> processes_;
    Shell shell_;
};
