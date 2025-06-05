#include "taskmaster.hpp"

int main(int argc, char* argv[]) {
    std::string configPath = "config/taskmaster.yml";
    if (argc > 1) configPath = argv[1];

    Taskmaster tm(configPath);
    tm.run();
    return 0;
}
