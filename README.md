# Pokemon Battle Simulator (WORK IN PROGRESS)

Welcome to my version of the **Pokemon Battle Simulator**! This project is a simulation of Pokemon battles, allowing players to create teams, select moves, and engage in battles with opponents. The simulator is designed to replicate the mechanics of Pokemon battles, including types, moves, status effects, and more but with my own Personal Twist.

---

## Features
- **Team Creation**: Build your own Pokemon team with custom moves and items.
- **Battle Mechanics**: Simulates turn-based battles with type advantages, move categories, and status effects.
- **Environment Simulation**: Includes weather effects and other environmental factors.
- **Logging**: Records battle logs for analysis and debugging.
- **Customizable**: Easily extendable to add new Pokemon, moves, and features.

---

## Current Status
The project is still a **work in progress** and does not work as intended yet. There are several **bugs and issues** that need to be identified and resolved. As a result:
- The program may not run as expected in some cases.
- Certain features may not function correctly or may cause crashes.
- Debugging and further development are required to make the simulator fully operational.

---

## Folder Structure
Here’s an overview of the files in the project for now:

### Source Files
- **`main.cpp`**: The entry point of the program. Initializes the game and starts the simulation.
- **`battle.cpp`**: Implements the battle mechanics, including turn-based logic and move execution.
- **`data_loader.cpp`**: Handles loading data from external files (e.g., Pokemon, moves, items).
- **`environment.cpp`**: Manages environmental effects like weather and terrain.
- **`game.cpp`**: Contains the main game loop and overall game logic.
- **`item.cpp`**: Implements item effects and interactions during battles.
- **`move.cpp`**: Defines move properties and their effects.
- **`pokemon.cpp`**: Implements Pokemon attributes, stats, and behaviors.
- **`record_log.cpp`**: Handles logging of battle events for debugging or replay purposes.
- **`status.cpp`**: Manages status effects like paralysis, burn, and poison.
- **`team.cpp`**: Handles team creation and management.
- **`types.cpp`**: Defines type advantages and interactions.

### Header Files
- Each `.cpp` file has a corresponding `.h` file (e.g., `battle.h`, `pokemon.h`) that defines the classes, functions, and constants used in the implementation.

### Configuration Files
- **`.vscode/tasks.json`**: Configures the build tasks for compiling the project using Cygwin or other compilers.
- **`.vscode/launch.json`**: Configures the debugger for running and debugging the project.

### Data Files
- **`pokemon.csv`**: Contains data about Pokemon (e.g., stats, types, abilities).
- **`moves.csv`**: Contains data about moves (e.g., power, accuracy, type).
- **`items.csv`**: Contains data about items (e.g., effects, usage).

---

## Prerequisites
To build and run the project, you need the following:
- **C++ Compiler**: GCC (via Cygwin or MinGW), MSVC, or any C++17-compatible compiler.
- **Build System**: Visual Studio Code with configured `tasks.json` and `launch.json`.
- **Cygwin/MinGW**: If using GCC on Windows, ensure Cygwin or MinGW is installed and properly configured.

---

## How to Build and Run

### Using Visual Studio Code
1. Open the project folder in Visual Studio Code.
2. Ensure the compiler is set up (e.g., Cygwin or MinGW).
3. Press `Ctrl+Shift+B` to build the project.
4. If the build is successful, run the executable:
   ```bash
   ./PokemonBattleSimulator.exe

---

### Using Command Line
1. Open a terminal (e.g., Cygwin Terminal or Command Prompt) and navigate to the project folder:
   ```bash
   cd /path/to/PokemonBattleSim
   ```
2. Compile the project using `g++`:
   ```bash
   g++ -std=c++17 -g main.cpp battle.cpp data_loader.cpp environment.cpp game.cpp item.cpp move.cpp pokemon.cpp record_log.cpp status.cpp team.cpp types.cpp -o PokemonBattleSimulator.exe
   ```
3. Run the executable:
   ```bash
   ./PokemonBattleSimulator.exe
   ```

---

## Future Improvements
- Fix existing bugs and issues to ensure the program runs as intended.
- Add more Pokemon, moves, and items.
- Implement AI for enemy trainers.
- Add a graphical user interface (GUI).
- Support multiplayer battles.
- Improve logging and debugging tools for better error tracking.
- Optimize performance for larger-scale battles.

---

## Credits
- Inspired by the Pokemon franchise.

---
