# C++ and Lua API Interfacing (Proof of Concept)

This repository serves as a **Proof of Concept (PoC)** demonstrating how a compiled native C++ application can seamlessly interface with a dynamic Lua scripting environment using the official Lua C API. 

In industrial robotics and UAV software architectures (such as ArduPilot), this pattern is widely used: the performance-critical core is written in C++, while the mission logic or configuration remains exposed to end-users via lightweight Lua scripts.

## Project Architecture Overview
1. **`config.lua`**: Defines global configuration variables and implements a native Lua function (`calculate_thrust`) to evaluate required drone motor forces.
2. **`main.cpp`**: Initializes the Lua Virtual Machine (VM), safe-loads the script, reads parameters from the Lua stack, and triggers the Lua execution loop directly from C++.

---

## Prerequisites & Installation

### 🐧 On Linux (Ubuntu/Debian)
Install the standard system development libraries for Lua and CMake:
```bash
sudo apt update
sudo apt install cmake g++ liblua5.3-dev
```

### 🪟 On Windows
1. Install **Visual Studio 2022** (with the *Desktop development with C++* workload).
2. Install **CMake** (v3.16+).
3. Download the precompiled Windows binaries of Lua from the official source or via a package manager like `vcpkg`:
   ```cmd
   vcpkg install lua:x64-windows
   ```

---

## Compilation and Execution

### 🚀 Quick Build (Linux & Windows Command Line)
From the root folder of the project, run the following commands to generate the build files and compile the executable:

```bash
# 1. Create and navigate to the build directory
mkdir build && cd build

# 2. Configure the project with CMake
cmake ..

# 3. Compile the executable
cmake --build .

# 4. Copy the config script next to the binary
cp ../config.lua .    # (Use 'copy ..\config.lua .' on Windows)

# 5. Run the program
./lua_test            # (Use 'lua_test.exe' on Windows)
```

### Expected Console Output
Upon execution, you should witness bidirectional data exchange through the Lua Virtual Machine stack:
```text
[C++] Data read from Lua -> Name: Quad_Pro_2026 | Max Alt: 150m

[Lua] Calcul de la poussée requis pour 2.5kg...
[C++] Result returned by Lua -> Total thrust required : 29.43 Newtons.
```

---

## Going Further: Modern C++ Wrappers

While this proof of concept directly utilizes the raw **Lua C API** (managing the low-level indexing of the `lua_State` stack manually), production-grade applications usually wrap this behavior to prevent memory leaks and human indexing errors.

To transition this project into a robust, object-oriented production system, we highly recommend integrating one of the following industry-standard C++ header-only libraries:

* **[Sol2](https://github.com/ThePhD/sol2.git)**: Currently the most popular, high-performance C++17/C++20 Lua wrapper. It provides exceptional type safety, handles advanced bindings easily, and completely automates stack push/pop sequences.
* **[LuaBridge](https://github.com/vinniefalco/LuaBridge.git)**: A lightweight, clean, and reliable library designed to map C++ classes, functions, and methods directly into Lua code without external dependencies.
