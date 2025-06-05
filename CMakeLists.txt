cmake_minimum_required(VERSION 3.12)
project(taskmaster)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

add_executable(taskmaster ${SOURCES})