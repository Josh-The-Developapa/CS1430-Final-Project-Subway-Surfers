#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_mixer.h>

#include <vector>

#include "GameObjects.h"
#include "Renderer.h"
#include "SDL_Plotter.h"

class SubwaySurferGame {
   private:
    SDL_Plotter& plotter;
    Renderer renderer;
    int screenWidth, screenHeight;

    int currentLane;
    float playerY;
    float verticalVelocity;
    bool isJumping;
    float animTime;

    std::vector<Obstacle> obstacles;
    std::vector<Collectible> collectibles;
    std::vector<Particle> particles;
    int score, lives, level;
    float gameTime;
    float scrollSpeed;
    int gameState;

    float bgScroll;
    int comboMultiplier;
    float comboTimer;
    bool showInstructions;
    float instructionTimer;
    Mix_Music* bgMusic;

    // description: puts initial obstacles in the game
    // return: void
    // precondition: game initialized
    // postcondition: obstacles vector filled with starting obstacles
    void spawnInitialObstacles();

    // description: makes particle effects at a spot
    // return: void
    // precondition: coords and colors valid
    // postcondition: count particles added to vector with r,g,b colors
    void spawnParticles(int x, int y, int count, int r, int g, int b);

public:
    // description: makes the game object
    // return: N/A (constructor)
    // precondition: SDL_Plotter initialized
    // postcondition: game created with starting values, music loaded
    SubwaySurferGame(SDL_Plotter& g);

    // description: cleans up game object
    // return: N/A (destructor)
    // precondition: game exists
    // postcondition: music freed, game destroyed
    ~SubwaySurferGame();

    // description: updates game based on key pressed
    // return: void
    // precondition: game state valid, key is input char
    // postcondition: player moved, obstacles updated, collisions checked, score changed
    void update(char key);

    // description: draws everything to screen
    // return: void
    // precondition: game state valid, plotter ready
    // postcondition: game objects and UI drawn on screen
    void render();

    // description: resets game back to start
    // return: void
    // precondition: game exists
    // postcondition: variables reset, obstacles respawned, player at start position
    void resetGame();
};

#endif