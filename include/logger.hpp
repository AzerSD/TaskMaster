#pragma once
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    Logger(const std::string& path);
    void log(const std::string& message);

private:
    std::ofstream file_;
    std::mutex mtx_;
};
