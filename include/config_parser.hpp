#pragma once
#include "program_config.hpp"
#include <map>
#include <string>

class ConfigParser {
public:
    ConfigParser(const std::string& path);
    std::map<std::string, ProgramConfig> parse();

private:
    std::string path_;
};
