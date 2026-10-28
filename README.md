# Interview-Netatmo

This project is a small C++ cellular automaton simulation inspired by Conway's Game of Life. It models a 2D grid of cells, updates their states according to custom rules, and renders the evolving world in the terminal.

## Overview

The program is organized around three main components:

- `World`: stores the grid dimensions and the state of each cell
- `Engine`: applies the transition rules from one generation to the next
- `Rendering`: prints the current state of the world to the console

The implementation is split between:

- `technical_test.hpp` — declarations for the classes
- `technical_test.cpp` — logic implementation and the simulation loop

## How it works

Each cell is represented as:

- `0` = dead / inactive
- `1` = alive / active

For each cell, the program inspects neighboring cells and counts how many are alive. Depending on that count, the cell may stay alive, die, or become active.

This project uses custom rules:

- `inactive_to_active_Rules = {3, 6, 7, 8}`
- `remain_active_Rules = {3, 4, 6, 7, 8}`

These rules are applied iteratively to generate the evolution of the world.

## Project structure

```text
.
├── README.md
├── technical_test.hpp
├── technical_test.cpp
├── technical_test
└── ...

## Build and Run

### Prerequisites
- A C++ compiler supporting **C++23** (e.g., `g++` 13+ or `clang++` 16+)

### Compilation
Compile the project using the following command:

```bash
g++ -Wall -Wextra -std=c++23 technical_test.cpp -o technical_test


###Execution

Run the generated executable:

```bash
./technical_test

