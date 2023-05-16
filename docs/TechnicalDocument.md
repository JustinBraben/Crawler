# Title: "Crawler" Technical Design Document (Entity Component System)

## Language and Libraries

-   C++ (C++17 or later)
-   SFML (Simple and Fast Multimedia Library) for graphics, audio, and input

## Core Systems and Components

### 1. Game Engine

-   Main game loop
-   State management (game states: main menu, gameplay, pause, game over)
-   Resource management (textures, sounds, fonts)
-   Event handling

### 2. Entity Component System (ECS)

-   Implement a custom ECS engine to efficiently manage entities, components, and systems
-   Entities as unique IDs (e.g., using `std::size_t`)
-   Components as plain data structures
-   Systems as classes with an `update()` method to process entities with specific component sets

### 3. Rendering

-   Rendering system for drawing entities with `SpriteComponent` and `TransformComponent`
-   Text rendering for UI elements

### 4. Audio

-   Audio system for background music and sound effect playback based on `AudioComponent`
-   Volume and audio settings

### 5. Input

-   Input system for handling keyboard, mouse, and gamepad input based on `InputComponent`
-   Keybinding configuration

## Data Structures and Algorithms

### 1. Dungeon Generation

-   Procedurally generated dungeons using a combination of algorithms:
    -   Randomized Prim's Algorithm for maze generation
    -   Cellular Automata for cave-like areas
    -   Binary Space Partitioning for room-based dungeons
-   Dungeon generation system that creates entities and assigns components (e.g., `TransformComponent`, `SpriteComponent`, `ColliderComponent`) based on the generated layout

### 2. Pathfinding and AI

-   A* algorithm for pathfinding
-   AI system to process entities with `AIComponent` and `PathComponent`

### 3. Character and Enemy Entities

-   Components for representing common attributes (e.g., `TransformComponent`, `HealthComponent`, `SpriteComponent`)
-   Additional components for specific functionality (e.g., `PlayerControlComponent`, `AIComponent`, `InventoryComponent`, `EquipmentComponent`)
-   Systems to manage entities with specific component sets (e.g., `PlayerControlSystem`, `AISystem`, `InventorySystem`, `EquipmentSystem`)

### 4. Collision Detection

-   `ColliderComponent` for representing entity colliders
-   Collision system to handle collisions between entities with `ColliderComponent` and `TransformComponent`
-   Quadtree data structure for efficient broad-phase collision detection

### 5. Inventory and Equipment

-   Components for representing inventory and equipment (e.g., `InventoryComponent`, `EquipmentComponent`)
-   Inventory and equipment systems for managing item interactions and equipping/unequipping items

### 6. Saving and Loading

-   Serialization and deserialization of game data (e.g., component data, dungeon layout)
-   File input/output using C++ streams (e.g., `std::ifstream`, `std::ofstream`)
-   JSON or binary format for saved game data

## Scene Management System

-   In order to manage the different scenes of the game (e.g., menu, gameplay, game won), a Scene Management System can be implemented
-   This system will be responsible for controlling the game flow, orchestrating the transitions between different scenes, and managing the lifecycle of each scene

### 1. Scene Base Class

-   Create a base Scene class that other specific scenes (e.g., `Scene_Menu`, `Scene_Play`, `Scene_Won`) can inherit from
-   This base class should include methods for initializing the scene, handling input, updating the scene, and rendering the scene
-   These methods will be overridden by each specific scene
-   Also, this class will include a method for managing scene transitions

### 2. Scene Manager Class

-   Implement a `SceneManager` class that will be responsible for managing the game's scenes
-   The `SceneManager` will maintain a stack-like structure to manage scenes, the current active scene will be on the top of the stack
-   When transitioning between scenes, the `SceneManager` will handle pushing new scenes to the stack, popping scenes from the stack, or replacing the current scene

### 3. Scene Implementations

-   Implement specific scene classes that inherit from the base `Scene` class, these could include `Scene_Menu`, `Scene_Play`, `Scene_Won`, etc
-   Each scene will override the methods from the base `Scene` class for initializing the scene, handling input, updating the scene, and rendering the scene

### 4. Scene Transitions

-   When a scene transition occurs (for example, the player moves from the menu scene to the gameplay scene), the `SceneManager` will push the new scene onto the stack, making it the active scene
-   The previous scene can either be paused or destroyed depending on the needs of the game
-   Transitions between scenes can be enhanced with various effects (fade in/out, slide, etc.) to provide a more polished game experience

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
-   Regular code reviews and refactoring to maintain code quality

By using an Entity Component System (ECS) architecture for the "Dungeon Explorer" game, you will be able to create a flexible and efficient game engine that allows entities to have any number of specified components. Systems will control how these entities behave, resulting in a highly modular and adaptable game structure.