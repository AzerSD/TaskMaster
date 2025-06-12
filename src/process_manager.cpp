#include "process_manager.hpp"
#include <sstream>      // For std::istringstream
#include <iostream>     // For std::cerr, std::cout
#include <unistd.h>     // For fork(), execve(), chdir(), _exit(), and STDERR_FILENO
#include <fcntl.h>      // For open() and O_APPEND
#include <sys/types.h>  // For pid_t
#include <sys/stat.h>   // For umask()
#include <unordered_map> // For std::unordered_map
#include <signal.h>     // For signal handling
#include <chrono>       // For time handling
#include <thread>       // For sleep_for()
#include <sys/wait.h>   // For waitpid()


int strToSignal(const std::string& sig) {
    static std::unordered_map<std::string, int> sigMap = {
        {"HUP", SIGHUP}, {"INT", SIGINT}, {"QUIT", SIGQUIT}, {"ILL", SIGILL},
        {"ABRT", SIGABRT}, {"FPE", SIGFPE}, {"KILL", SIGKILL}, {"SEGV", SIGSEGV},
        {"PIPE", SIGPIPE}, {"ALRM", SIGALRM}, {"TERM", SIGTERM}, {"USR1", SIGUSR1},
        {"USR2", SIGUSR2}
    };
    auto it = sigMap.find(sig);
    return (it != sigMap.end()) ? it->second : SIGTERM;
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
    int sig = strToSignal(config_.stopSignal);

    for (pid_t pid : pids_) {
        if (kill(pid, sig) == -1) {
            perror(("Failed to send stop signal to PID " + std::to_string(pid)).c_str());
            continue;
        }

        std::cout << "Sent signal " << sig << " to PID " << pid << std::endl;

        // Wait for graceful exit
        auto start = std::chrono::steady_clock::now();
        while (true) {
            if (waitpid(pid, nullptr, WNOHANG) > 0) break;

            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
            if (elapsed >= config_.stopTime) {
                std::cout << "Grace period expired. Sending SIGKILL to PID " << pid << std::endl;
                kill(pid, SIGKILL);
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    pids_.clear();
}

void ProcessManager::restart() {
    stop();
    start();
}

bool ProcessManager::isRunning(pid_t pid) {
    return (kill(pid, 0) == 0);
}

void ProcessManager::status() const {
    std::cout << "[" << config_.name << "] Status:" << std::endl;
    if (pids_.empty()) {
        std::cout << "  No running processes.\n";
        return;
    }

    for (pid_t pid : pids_) {
        std::string state = (kill(pid, 0) == 0) ? "Running" : "Not running";
        std::cout << "  PID " << pid << ": " << state << std::endl;
    }
}


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



