#pragma once
#include <string>

class Taskmaster; // forward declaration

class Shell {
public:
    Shell(Taskmaster* parent);
    void start();

private:
    Taskmaster* taskmaster_;
    void handleCommand(const std::string& input);
};
