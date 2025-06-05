#include "shell.hpp"
#include <iostream>

Shell::Shell(Taskmaster* parent) : taskmaster_(parent) {}

void Shell::start() {
    std::string input;
    while (true) {
        std::cout << "taskmaster> ";
        std::getline(std::cin, input);
        handleCommand(input);
    }
}

void Shell::handleCommand(const std::string& input) {
    // Parse and execute shell commands
}
