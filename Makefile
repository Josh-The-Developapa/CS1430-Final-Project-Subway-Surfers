# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall \
	-I/opt/homebrew/include \
	-I/opt/homebrew/opt/sdl2/include \
	-I/opt/homebrew/opt/sdl2_mixer/include

LDFLAGS = -L/opt/homebrew/lib \
	-L/opt/homebrew/opt/sdl2/lib \
	-L/opt/homebrew/opt/sdl2_mixer/lib

LIBS = -lSDL2 -lSDL2_mixer

# Directories
SRC_DIR = src
BUILD_DIR = build

# Target executable
TARGET = program

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
	mkdir -p $(BUILD_DIR)

# Link the executable
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run