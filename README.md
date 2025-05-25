# Coup Game (C++)

## Project Overview

This project implements the board game **Coup** in C++ with:

- A complete GUI using SFML
- Full game logic, role mechanics, and turn handling
- Unit tests written with doctest
- Verified to be memory-safe with Valgrind

---

## Dependencies

Make sure the following are installed on your system:

- **g++** (with C++20 support)
- **SFML** (Simple and Fast Multimedia Library)
- **Valgrind** (for memory leak detection)
- **doctest.h** (included in the repo or downloaded from [doctest GitHub](https://github.com/doctest/doctest))

On Debian/Ubuntu (including Kali Linux), install with:

```bash
sudo apt update
sudo apt install g++ libsfml-dev valgrind
```

---

## Build & Run

### 1. Compile the game (GUI)

```bash
make Main
```

### 2. Launch the game

```bash
./Main
```

### 3. Run the unit tests

```bash
make test
```

### 4. Run Valgrind on the GUI

```bash
make valgrind
```

> No memory leaks are present. All dynamic allocations (e.g. players) are managed by the `Game` destructor.

---

## Features

- Support for all roles:
  - Governor
  - Spy
  - Baron
  - General
  - Judge
  - Merchant
- Fully functional GUI screens:
  - Opening screen
  - Player setup
  - Name entry and role reveal
  - In-game action menu
  - Popups for undo/coup/target selection
  - Endgame screen
- Turn management, role abilities, sanctions, and undo mechanics
- Tested using `doctest.h` with over 100 checks

---

## Tests & Validation

- All logic is verified in `test.cpp`
- Tests cover:
  - Player actions
  - Role-specific effects
  - Edge cases (e.g. dead players, forced coup)
- Valgrind output:
  - All player memory freed correctly
  - SFML/OpenGL-related leaks (expected, external)

---

## Project Structure

```
├── src/
│   ├── Game.cpp / Game.hpp
│   ├── Player.cpp / Player.hpp
│   └── [RoleName].cpp / .hpp
├── GUI/
│   └── [All screen + popup files]
├── test.cpp
├── main.cpp
├── Makefile
└── README.md
```

---

## Author

Ofek Bar-Shalom  
Email: ofekbarshalom@gmail.com
