# 🧩 Taskmaster (C++ Job Control System)

## 📘 Project Description

**Taskmaster** is a job control system inspired by `supervisord`. It monitors and manages long-running processes based on a configuration file. It supports process control, automatic restarts, and a command-line interface for interacting with managed processes.

This project is implemented in **C++**, using only the **standard library** (with exceptions for parsing config files). It is designed to run in the foreground and not as a true daemon.

---

## ✅ To-Do List

### 🔧 Core Functionality

- [x] Parse configuration file (YAML or custom format)
- [x] Launch processes based on configuration
- [ ] Monitor processes and track status (alive/dead)
- [ ] Implement auto-restart logic based on config
- [ ] Handle `SIGHUP` to reload configuration
- [ ] Hot-reload without affecting unchanged processes
- [ ] Implement process logging system (file-based)

### 🖥️ Control Shell

- [ ] Start interactive shell in foreground
- [ ] Add command: `status`
- [ ] Add command: `start <name>`
- [ ] Add command: `stop <name>`
- [ ] Add command: `restart <name>`
- [ ] Add command: `reload`
- [ ] Add command: `exit`
- [ ] Implement line editing & command history

### 📁 Configuration Support

- [ ] Support all required config options:
  - [ ] `cmd`
  - [ ] `numprocs`
  - [ ] `autostart`
  - [ ] `autorestart` (always / never / unexpected)
  - [ ] `exitcodes`
  - [ ] `startretries`, `starttime`
  - [ ] `stopsignal`, `stoptime`
  - [ ] `stdout`, `stderr`
  - [ ] `env`
  - [ ] `workingdir`
  - [ ] `umask`

### 🧪 Testing & Edge Cases

- [ ] Handle invalid config entries
- [ ] Handle programs that crash immediately
- [ ] Simulate manual process kills
- [ ] Test high-output programs
- [ ] Test multiple process instances per program

---

## 🎯 Learning Objectives

- Deep understanding of Unix **process management** (fork/exec, signals, waitpid)
- Mastering **inter-process communication**
- Advanced **file I/O** and **logging**
- Using **signals** in C++ (`signal`, `sigaction`)
- Implementing a **command-line interface** from scratch
- Working with **configuration files** (YAML or manual parsing)
- Managing **process groups** and **graceful shutdowns**

---

## 🛠 Recommended Tools / Libraries

- **C++17+** with STL
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) – for YAML parsing (optional)
- `std::thread`, `std::mutex`, `std::condition_variable` – for concurrency
- `readline` or custom implementation – for CLI editing/history
- `std::filesystem` – for file and directory handling

---

## 🔗 References

- [`supervisord`](http://supervisord.org/) – inspiration/reference
- `man 2 fork`, `man 2 execve`, `man 2 waitpid`
- `man 7 signal`, `man 2 kill`
- [Linux Process Management Guide (TLPI)](https://man7.org/tlpi/)

---

## 📦 Final Deliverable

- Source code with Makefile
- Example configuration file
- README and documentation
- Test scripts or manual test cases

---

## ✍ Author

- Azer Sioud | asioud

