cmake_minimum_required(VERSION 3.10)
project(taskmaster)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/yaml-cpp)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/yaml-cpp/include
)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(taskmaster ${SOURCES})

# Link yaml-cpp
target_link_libraries(taskmaster yaml-cpp)
