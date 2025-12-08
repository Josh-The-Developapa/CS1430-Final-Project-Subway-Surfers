# Detect operating system
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Platform-specific settings
ifeq ($(DETECTED_OS),Windows)
    # Windows-specific settings
    INCLUDE_DIRS = -IC:/SDL2/include
    LIB_DIRS = -LC:/SDL2/lib
    LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
    TARGET = Game_Executable.exe
    MKDIR = if not exist $(subst /,\,$(BUILD_DIR)) mkdir $(subst /,\,$(BUILD_DIR))
    RM = rmdir /s /q
    PATH_SEP = \\
    RUN_CMD = $(TARGET)
else ifeq ($(DETECTED_OS),Darwin)
    # macOS-specific settings
    INCLUDE_DIRS = -I/opt/homebrew/include \
                   -I/opt/homebrew/opt/sdl2/include \
                   -I/opt/homebrew/opt/sdl2_mixer/include
    LIB_DIRS = -L/opt/homebrew/lib \
               -L/opt/homebrew/opt/sdl2/lib \
               -L/opt/homebrew/opt/sdl2_mixer/lib
    LIBS = -lSDL2 -lSDL2_mixer
    TARGET = Game_Executable
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf
    PATH_SEP = /
    RUN_CMD = ./$(TARGET)
else
    # Linux-specific settings
    INCLUDE_DIRS = -I/usr/include/SDL2
    LIB_DIRS = -L/usr/lib
    LIBS = -lSDL2 -lSDL2_mixer
    TARGET = Game_Executable
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf
    PATH_SEP = /
    RUN_CMD = ./$(TARGET)
endif

# Add include directories to compiler flags
CXXFLAGS += $(INCLUDE_DIRS)
LDFLAGS = $(LIB_DIRS)

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
	$(SRC_DIR)/Game.cpp \
	$(SRC_DIR)/Renderer.cpp \
	$(SRC_DIR)/GameObjects.cpp \
	$(SRC_DIR)/Constants.cpp \
	$(SRC_DIR)/SDL_Plotter.cpp

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Header files (for dependency tracking)
HEADERS = $(SRC_DIR)/Game.h \
	$(SRC_DIR)/Renderer.h \
	$(SRC_DIR)/GameObjects.h \
	$(SRC_DIR)/Constants.h \
	$(SRC_DIR)/SDL_Plotter.h

# Default target
all: $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	$(MKDIR)

# Link the executable
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
ifeq ($(DETECTED_OS),Windows)
	$(RM) $(subst /,\,$(BUILD_DIR)) 2>nul || exit 0
	del /f /q $(TARGET) 2>nul || exit 0
else
	$(RM) $(BUILD_DIR) $(TARGET)
endif

# Run the game
run: $(TARGET)
	$(RUN_CMD)

# Phony targets
.PHONY: all clean run

# Display detected OS (helpful for debugging)
info:
	@echo Detected OS: $(DETECTED_OS)
	@echo Target: $(TARGET)
	@echo Compiler: $(CXX)