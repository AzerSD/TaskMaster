#include "logger.hpp"
#include <ctime>

Logger::Logger(const std::string& path) {
    file_.open(path, std::ios::app);
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::time_t now = std::time(nullptr);
    file_ << std::ctime(&now) << ": " << message << std::endl;
}
