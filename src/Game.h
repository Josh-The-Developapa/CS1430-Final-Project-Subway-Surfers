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

    void spawnInitialObstacles();
    void spawnParticles(int x, int y, int count, int r, int g, int b);

   public:
    SubwaySurferGame(SDL_Plotter& g);
    ~SubwaySurferGame();

    void update(char key);
    void render();
    void resetGame();
};

#endif