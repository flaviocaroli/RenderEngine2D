# 2D RPG Game Project

## Introduction
Welcome to the 2D RPG Game Project, a custom-built game engine and role-playing game developed in C++. This project utilizes SDL2 for graphical rendering, and handling user inputs to create a basic game experience.

## Prerequisites
Before building and running the game, you will need to install the following dependencies:

- C++ Compiler (C++17 or later)
- CMake (version 3.15 or higher)
- SDL2 libraries: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

## Installation of Dependencies

### Linux (Ubuntu/Debian)
Open a terminal and run the following commands:
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```


## Prepare the Build Environment
Navigate to the project root directory and create a build directory:
```bash
mkdir build
cd build
```
Configure the project using CMake:
```bash
cmake ..
```
Build the project:
```bash
cmake --build .
```

After building, run the executable from the build directory:
```bash

./FrammentiDiSogno
```
## Basic commands:

While playing *Dream Frame*, you can use the following keyboard commands to navigate and interact within the game environment:

- **W, A, S, D** - Move the player character up, left, down, or right.
- **SPACE** - Run while moving. Press SPACE while pressing W, A, S, or D to make the character run in the corresponding direction.
- **J** - Jump while moving. Press J while moving to execute a jump animation.
- **E** - Interact with nearby NPCs to initiate through dialogues.
- **SPACE** - To contiune and finish dialogue interadtions

### Special Notes
- The camera follows the player character to always keep them at the center of the view.
- The player character stops moving when reaching the boundaries of the map to prevent going off the visible area.
