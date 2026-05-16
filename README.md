# Doodle Jump

## Introduction
Doodle Jump is a challenging and addictive 2D platformer game developed in C++ using the SFML (Simple and Fast Multimedia Library). The objective is to jump as high as possible by hopping on platforms while avoiding enemies and pitfalls.

The project demonstrates several core Object-Oriented Programming (OOP) concepts, including:
- **Polymorphism**: Used for different types of platforms and game entities.
- **Encapsulation**: Game logic is divided into specialized classes like `GameEngine`, `GameLoop`, and `SoundManager`.
- **Inheritance**: A base entity class provides common functionality for platforms and the player.
- **RTTI (Run-Time Type Identification)**: Used for dynamic type checking during collisions.
- **Design Patterns**: Implementation of the Singleton pattern for the `SoundManager` and `Logger`.

## File Structure
```text
.
├── main.cpp                # Entry point of the application
├── makefile                # Build configuration for automation
├── src/                    # Source files implementing game logic
│   ├── BaseEntity.cpp      # Base class for all game objects
│   ├── Doodler.cpp         # Player character logic and physics
│   ├── Enemy.cpp           # Enemy behavior and movement
│   ├── FastPlatform.cpp    # Platform with fast-moving behavior
│   ├── GameEngine.cpp      # Core engine, physics, and collision detection
│   ├── GameLoop.cpp        # Manages the main game loop and state
│   ├── Keyboard.cpp       # Handles player input
│   ├── Logger.cpp          # Simple logging utility
│   ├── Platform.cpp        # Base platform logic
│   ├── PlatformCreator.cpp # Factory class for creating platforms
│   ├── RegularPlatform.cpp # Standard platform behavior
│   ├── SlowPlatform.cpp    # Platform with slow-moving behavior
│   ├── Score.cpp           # Handles game scoring
│   ├── SoundManager.cpp    # Manages audio and background music
│   └── StartMenu.cpp       # Implementation of the initial game menu
├── inc/                    # Header files (definitions and declarations)
│   └── ...                 # Corresponding .hpp files for all source classes
└── res/                    # Game resources (Assets)
    ├── font/               # Game fonts (e.g., arial.ttf)
    ├── img/                # Game textures and backgrounds
    └── sounds/             # Audio clips and background music
```

## Requirements
To compile and run the game, you need:
- **C++17** compatible compiler (GCC/Clang/MSVC)
- **SFML 2.x** (Simple and Fast Multimedia Library)

## How to Compile and Run

### Linux (Fedora/Ubuntu/Debian)
1. **Install SFML Dependencies**:
   - For Fedora: `sudo dnf install SFML-devel`
   - For Ubuntu/Debian: `sudo apt-get install libsfml-dev`

2. **Build the Project**:
   The project includes a `makefile` to automate the build process. Simply run:
   ```bash
   make
   ```
   *This will compile all source files and link the SFML libraries.*

3. **Run the Game**:
   ```bash
   ./doodle-jump
   ```

### Windows
1. **Install a Compiler**: 
   - Install [MinGW-w64](https://www.mingw-w64.org/) or use [Visual Studio](https://visualstudio.microsoft.com/).
2. **Setup SFML**:
   - Download the SFML binaries matching your compiler version.
   - Configure your IDE to include the SFML `include` folder and link the `lib` folder.
3. **Link Libraries**:
   - Link the following SFML modules: `sfml-graphics`, `sfml-window`, `sfml-system`, and `sfml-audio`.
4. **Compile and Run**:
   - Build the project using your IDE or a command-line compiler and run the resulting `.exe`.

---
