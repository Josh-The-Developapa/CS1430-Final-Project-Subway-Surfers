#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>

#include "GameObjects.h"
#include "SDL_Plotter.h"

class Renderer {
   private:
    SDL_Plotter& plotter;
    int screenWidth;
    int screenHeight;

   public:
    Renderer(SDL_Plotter& g, int w, int h);

    void drawChar(int x, int y, char c, int r, int g, int b, int scale = 1);
    void drawText(int x, int y, const std::string& text, int r, int g, int b, int scale = 1);
    void drawTextCentered(int y, const std::string& text, int r, int g, int b, int scale = 1);
    void drawTextWithShadow(int x, int y, const std::string& text, int r, int g, int b, int scale = 1);
    void drawTextCenteredWithShadow(int y, const std::string& text, int r, int g, int b, int scale = 1);

    void drawGradientRect(int x, int y, int w, int h, int r1, int g1, int b1, int r2, int g2, int b2);
    void drawCircle(int cx, int cy, int radius, int r, int g, int b);
    void drawBox(int x, int y, int w, int h, int r, int g, int b);

    void drawTerrain(float bgScroll, float gameTime);
    void drawBuilding(int x, int y, int w, int h, int r, int g, int b);

    void drawPlayer(int currentLane, float playerY, float animTime);
    void drawObstacles(const std::vector<Obstacle>& obstacles);
    void drawCollectibles(const std::vector<Collectible>& collectibles);
    void drawParticles(const std::vector<Particle>& particles);

    void drawHUD(int score, int lives, int level, int comboMultiplier, float comboTimer,
                 bool showInstructions, float instructionTimer, int gameState);
    void drawStartScreen();
    void drawGameOverScreen(int score, int level);
    void drawPauseScreen();
};

#endif