# Modern C++ and Lua Interfacing using Sol2 (Proof of Concept)

This repository demonstrates how to integrate the **Sol2** library to interface a native C++17 application with a Lua scripting runtime. 

Unlike the raw Lua C API, **Sol2** is a modern, header-only C++ wrapper that eliminates manual stack manipulation (`lua_push`/`lua_pop`) and replaces it with intuitive, type-safe, and object-oriented syntax.

## Project Structure
```text
lua_cpp_sol2/
├── config.lua        # Lua script with variables and thrust function
├── main.cpp          # C++ source code using Sol2
└── sol/              # Sol2 header-only library directory (sol.hpp, etc.)
```

---

## Configuration Script (`config.lua`)
```lua
drone_name = "Quad_Pro_2026"
max_altitude = 150

function calculate_thrust(weight, gravity)
    local safety_factor = 1.2
    print("[Lua] Computing required thrust for " .. weight .. "kg...")
    return weight * gravity * safety_factor
end
```

---

## Setup & Compilation Guides

### 🪟 Windows Setup via Code::Blocks (MinGW)

1. **Download Prerequisites:**
   * Download and install **Code::Blocks** (Choose the `codeblocks-XX.XXmingw-setup.exe` version to include the GCC compiler).
   * Download the **Lua Development Files for Windows** (Header files like `lua.h` and the compiled `.a` or `.lib` library).
   * Download the **Sol2 library** from GitHub and place the `sol/` folder directly inside your project directory.

2. **Configure the Project in Code::Blocks:**
   * Open Code::Blocks, create a new **Console Application** project, and select **C++**.
   * Replace the generated `main.cpp` code with the one provided in this repository.

3. **Compiler Settings (Search Directories):**
   * Go to **Project** -> **Build options...** -> Select your project name on the left root.
   * Go to the **Search directories** tab -> **Compiler** sub-tab.
   * Click **Add** and select the path to your **Lua include folder** (where `lua.h` is located).
   * Click **Add** again and select the path to your **Sol2 folder** (the directory containing the `sol/` folder).

4. **Linker Settings:**
   * While still in **Build options...**, go to the **Linker settings** tab.
   * Under **Link libraries**, click **Add** and browse to select your Lua library file (e.g., `liblua53.a` or `lua53.lib`).

5. **Enable C++17 Standard:**
   * Go to the **Compiler settings** tab -> **Compiler Flags**.
   * Scroll down or search to check the box: `Have G++ follow the C++17 ISO C++ language standard [-std=c++17]`.
   * Click **OK** to save all configuration options.

6. **Run the Project:**
   * Place your `config.lua` file inside the exact same folder where Code::Blocks generates the executable output (usually `bin/Debug/` or `bin/Release/`).
   * Press **F9** (Build and Run).

---

### 🐧 Linux Setup (Ubuntu/Debian)

1. **Install System Dependencies:**
   ```bash
   sudo apt update
   sudo apt install g++ liblua5.3-dev
   ```

2. **Fetch Sol2 Headers:**
   Download the `sol.hpp` single-header or the full `sol/` library and place it next to your `main.cpp`.

3. **Compile via Command Line:**
   ```bash
   g++ main.cpp -std=c++17 -llua5.3 -o lua_sol2_test
   ```

4. **Run:**
   ```bash
   ./lua_sol2_test
   ```

---

## Expected Output
```text
[C++ / Sol2] Donnees lues -> Nom: Quad_Pro_2026 | Alt Max: 150m

[Lua] Computing required thrust for 2.5kg...
[C++ / Sol2] Poussee totale requise : 29.43 Newtons.
```
