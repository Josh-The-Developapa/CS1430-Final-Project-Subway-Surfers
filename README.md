# Subway Surfer Game - C++ Project

A Subway Surfer-style endless runner game built with C++ and SDL2 for a Computer Science finals project.

## Project Structure

```
subway-surfer/
├── main.cpp              # Entry point and main game loop
├── Game.h                # Game class header
├── Game.cpp              # Game logic implementation
├── Renderer.h            # Rendering class header
├── Renderer.cpp          # All rendering functions
├── GameObjects.h         # Game object structures (Obstacle, Collectible, Particle)
├── GameObjects.cpp       # Game object implementations
├── Constants.h           # Game constants and font declaration
├── Constants.cpp         # Font initialization
├── SDL_Plotter.h         # SDL wrapper (provided library)
├── Makefile              # Build configuration
└── assets/
    └── memphis-trap-wav-349366.mp3  # Background music
```

## File Descriptions

### Core Files

- **main.cpp**: Initializes SDL, creates the game instance, and runs the main game loop
- **Game.h/cpp**: Contains the `SubwaySurferGame` class with all game logic, physics, collision detection, and game state management
- **Renderer.h/cpp**: Handles all rendering operations including terrain, player, obstacles, UI elements, and effects
- **GameObjects.h/cpp**: Defines structures for game entities (obstacles, collectibles, particles) and their methods
- **Constants.h/cpp**: Stores game constants (screen size, physics values, lane positions) and the bitmap font data

### Dependencies

- **SDL_Plotter.h**: Provided SDL2 wrapper library for graphics
- **SDL2**: Graphics library
- **SDL2_mixer**: Audio library for background music

## Building the Project

### Prerequisites

- g++ compiler with C++11 support
- SDL2 development libraries
- SDL2_mixer development libraries

### Important Note About the Makefile

**The included Makefile is configured for macOS with Homebrew-installed SDL2 libraries.** If you're on a different system (Linux, Windows, or different macOS setup), you'll need to modify the Makefile or use manual compilation.

### Platform-Specific Build Instructions

#### macOS (with Homebrew - Default Makefile):

```bash
# Install dependencies
brew install sdl2 sdl2_mixer

# Build and run
make
./program

# Or simply
make run

# Clean build files
make clean
```

#### Linux (Ubuntu/Debian):

You'll need to **edit the Makefile** to use standard Linux library paths, or compile manually:

```bash
# Install dependencies
sudo apt-get install libsdl2-dev libsdl2-mixer-dev

# Manual compilation
g++ -std=c++11 src/main.cpp src/Game.cpp src/Renderer.cpp src/GameObjects.cpp src/Constants.cpp src/SDL_Plotter.cpp \
-lSDL2 -lSDL2_mixer \
-o program && ./program
```

#### Windows (MinGW/MSYS2):

You'll need to **edit the Makefile** for Windows paths, or compile manually:

```bash
# Install SDL2 and SDL2_mixer development libraries first

# Manual compilation (adjust paths to your SDL2 installation)
g++ -std=c++11 src/main.cpp src/Game.cpp src/Renderer.cpp src/GameObjects.cpp src/Constants.cpp src/SDL_Plotter.cpp \
-IC:/path/to/SDL2/include \
-LC:/path/to/SDL2/lib \
-lSDL2 -lSDL2_mixer \
-o program.exe
```

### Modifying the Makefile for Your System

If you want to use the Makefile on a non-macOS system, edit these sections in the Makefile:

```makefile
# Change these paths to match your system's SDL2 installation
CXXFLAGS = -std=c++11 -Wall \
	-I/your/include/path \
	-I/your/sdl2/include/path

LDFLAGS = -L/your/lib/path \
	-L/your/sdl2/lib/path
```

For standard Linux installations, you can often remove the custom include/lib paths entirely and just use:

```makefile
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 
```

## Game Controls

- **A / Left Arrow**: Move left
- **D / Right Arrow**: Move right
- **W / Up Arrow / Space**: Jump
- **P**: Pause/Resume
- **Q**: Quit game
- **R**: Restart (on game over screen)
- **S / Space**: Start game (on start screen)

## How to Play

1. Switch lanes to avoid obstacles (barriers, trains, signs)
2. Collect coins for points and combo multipliers
3. Collect hearts for extra lives
4. Build combos by collecting multiple coins in succession
5. Survive as long as possible while the game speeds up

## Code Organization Benefits

This multi-file structure provides several advantages:

1. **Separation of Concerns**: Game logic, rendering, and data structures are cleanly separated
2. **Maintainability**: Each file has a focused responsibility
3. **Reusability**: Components can be easily modified or reused
4. **Compilation Efficiency**: Only modified files need recompilation
5. **Readability**: Easier to navigate and understand the codebase
6. **Collaboration**: Multiple developers can work on different files simultaneously

## Credits

Created as a Computer Science finals project implementing an endless runner game inspired by Subway Surfers.