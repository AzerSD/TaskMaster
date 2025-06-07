#include "process_manager.hpp"
#include <sstream>
#include <iostream>
#include <unistd.h>     // For fork(), execve(), chdir(), _exit(), and STDERR_FILENO
#include <fcntl.h>      // For open() and O_APPEND
#include <sys/types.h>  // For pid_t
#include <sys/stat.h>   // For umask()

ProcessManager::ProcessManager(const ProgramConfig& config)
    : config_(config) {}


std::vector<std::string> ProcessManager::tokenize(const std::string& cmd) {
    std::vector<std::string> result;
    std::istringstream iss(cmd);
    std::string token;
    while (iss >> token) {
        result.push_back(token);
    }
    return result;
}

void ProcessManager::start() {
    for (int i = 0; i < config_.numProcs; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            std::cerr << "Failed to fork for: " << config_.name << std::endl;
            continue;
        }

        if (pid == 0) {
            // Child process

            // Set working directory
            if (!config_.workingDir.empty()) {
                if (chdir(config_.workingDir.c_str()) != 0) {
                    perror("chdir failed");
                    _exit(1);
                }
            }

            // Set umask
            umask(config_.umask);

            // Redirect stdout
            if (!config_.stdoutPath.empty()) {
                int fd = open(config_.stdoutPath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) perror("stdout open failed");
                else dup2(fd, STDOUT_FILENO);
            }

            // Redirect stderr
            if (!config_.stderrPath.empty()) {
                int fd = open(config_.stderrPath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) perror("stderr open failed");
                else dup2(fd, STDERR_FILENO);
            }

            // Build environment
            std::vector<std::string> envs;
            std::vector<char*> envp;
            for (const auto& [k, v] : config_.env) {
                envs.push_back(k + "=" + v);
            }
            for (auto& e : envs)
                envp.push_back(const_cast<char*>(e.c_str()));
            envp.push_back(nullptr);

            // Prepare arguments
            std::vector<std::string> tokens = tokenize(config_.cmd);
            std::vector<char*> argv;
            for (auto& s : tokens)
                argv.push_back(const_cast<char*>(s.c_str()));
            argv.push_back(nullptr);

            // Exec
            execve(argv[0], argv.data(), envp.data());
            perror("execve failed");
            _exit(1);
        } else {
            // Parent process
            pids_.push_back(pid);
            std::cout << "Started [" << config_.name << "] PID: " << pid << std::endl;
        }
    }
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
