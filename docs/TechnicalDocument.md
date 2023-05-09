# Title: "Crawler" Technical Design Document

## Language and Libraries

-   C++ (C++17 or later)
-   SFML (Simple and Fast Multimedia Library) for graphics, audio, and input

## Core Systems and Components

### 1. Game Engine

-   Main game loop
-   State management (game states: main menu, gameplay, pause, game over)
-   Resource management (textures, sounds, fonts)
-   Event handling

### 2. Rendering

-   Tile-based rendering system for dungeon levels
-   Sprite rendering for characters, enemies, and items
-   Text rendering for UI elements
-   Particle system for visual effects

### 3. Audio

-   Background music and sound effect playback
-   Volume and audio settings

### 4. Input

-   Keyboard and mouse input handling
-   Gamepad input handling (optional)
-   Keybinding configuration

## Data Structures and Algorithms

### 1. Dungeon Generation

-   Procedurally generated dungeons using a combination of algorithms:
    -   Randomized Prim's Algorithm for maze generation
    -   Cellular Automata for cave-like areas
    -   Binary Space Partitioning for room-based dungeons
-   Data structures for representing dungeon layout:
    -   2D grid of tile objects
    -   Graph to represent connectivity between rooms and corridors

### 2. Pathfinding and AI

-   A* algorithm for pathfinding and enemy AI movement
-   Data structures for representing AI behaviors and state machines

### 3. Character and Enemy Entities

-   Object-Oriented design using inheritance and composition
-   Base entity class with common attributes and methods (position, health, etc.)
-   Derived classes for player characters and enemy types with unique attributes and behaviors
-   Component-based design for managing abilities, status effects, and AI behaviors

### 4. Collision Detection

-   Axis-Aligned Bounding Box (AABB) collision detection for tile-based environments
-   Quadtree data structure for efficient broad-phase collision detection

### 5. Inventory and Equipment

-   Container classes for inventory and equipment management (e.g., `std::vector`, `std::unordered_map`)
-   Custom item class hierarchy for different types of items (weapons, armor, consumables)

### 6. Saving and Loading

-   Serialization and deserialization of game data (e.g., character stats, dungeon layout, inventory)
-   File input/output using C++ streams (e.g., `std::ifstream`, `std::ofstream`)
-   JSON or binary format for saved game data

## Additional Libraries and Tools

### 1. ImGui

-   Immediate Mode Graphical User Interface for debugging and development tools

### 2. Tiled

-   Tilemap editor for creating and editing tile-based dungeon levels (optional)

### 3. JSON for Modern C++

-   JSON parsing library for handling configuration files and save data

## Coding Standards and Practices

-   Follow modern C++ best practices (e.g., RAII, smart pointers, move semantics)
-   Consistent naming conventions for variables, functions, and classes
-   Use of `auto` keyword to improve code readability and maintainability
-   Organize code using namespaces and folder structure