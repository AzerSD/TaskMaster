#pragma once
#include <string>
#include <vector>
#include <map>

struct ProgramConfig {
    std::string         name;
    std::string         cmd;
    int                 numProcs = 1;
    bool                autostart = true;
    std::string         autorestart = "unexpected"; // always, never, unexpected
    std::vector<int>    exitcodes = {};
    int                 startRetries = 3;
    int                 startTime = 5;
    std::string         stopSignal = "TERM";
    int                 stopTime = 10;
    std::string         stdoutPath;
    std::string         stderrPath;
    std::string         workingDir;
    int                 umask = 022;
    std::map<std::string, std::string> env;
};
