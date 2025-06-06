#include "config_parser.hpp"
#include <yaml-cpp/yaml.h>
#include <iostream>

ConfigParser::ConfigParser(const std::string& path) : path_(path) {}

std::map<std::string, ProgramConfig> ConfigParser::parse() {
    std::map<std::string, ProgramConfig> configs;
    YAML::Node root = YAML::LoadFile(path_);

    if (!root["programs"]) {
        throw std::runtime_error("Missing 'programs' key in config");
    }

    for (const auto& it : root["programs"]) {
        const std::string name = it.first.as<std::string>();
        const YAML::Node& node = it.second;

        ProgramConfig cfg;
        cfg.name = name;
        cfg.cmd = node["cmd"].as<std::string>();
        cfg.numProcs = node["numprocs"].as<int>(1);
        cfg.autostart = node["autostart"].as<bool>(true);
        cfg.autorestart = node["autorestart"].as<std::string>("unexpected");
        if (node["exitcodes"])
            for (auto code : node["exitcodes"])
                cfg.exitcodes.push_back(code.as<int>());

        cfg.startTime = node["starttime"].as<int>(5);
        cfg.startRetries = node["startretries"].as<int>(3);
        cfg.stopSignal = node["stopsignal"].as<std::string>("TERM");
        cfg.stopTime = node["stoptime"].as<int>(10);
        cfg.stdoutPath = node["stdout"] ? node["stdout"].as<std::string>() : "";
        cfg.stderrPath = node["stderr"] ? node["stderr"].as<std::string>() : "";

        if (node["env"]) {
            for (const auto& env : node["env"]) {
                cfg.env[env.first.as<std::string>()] = env.second.as<std::string>();
            }
        }

        cfg.workingDir = node["workingdir"].as<std::string>("");
        cfg.umask = node["umask"].as<int>(022);

        configs[name] = cfg;
    }

    return configs;
}
