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
    // description: The functin draws a  character at (x,y).
    // return: void
    // precondition: Valid screen coordinates.
    // postcondition: Character is drawn to screen.
    void drawChar(int x, int y, char c, int r, int g, int b, int scale = 1);
    // description: The function draws text starting at (x,y).
    // return: void
    // precondition: Valid string and coordinates.
    // postcondition: Text appears on screen.
    void drawText(int x, int y, const std::string& text, int r, int g, int b, int scale = 1);
    // description: The function draws horizontally centered text at y.
    // return: void
    // precondition: Valid string; y inside screen.
    // postcondition: Centered text is rendered.
    void drawTextCentered(int y, const std::string& text, int r, int g, int b, int scale = 1);
    // description: The function draws text with a shadow behind it.
    // return: void
    // precondition: Valid string and coords.
    // postcondition: Text with shadow appears on screen.
    void drawTextWithShadow(int x, int y, const std::string& text, int r, int g, int b, int scale = 1);
    // description: The function draws centered text with a shadow.
    // return: void 
    // precondition: Valid string; y within screen.
    // postcondition: Centered shadow text is rendered.
    void drawTextCenteredWithShadow(int y, const std::string& text, int r, int g, int b, int scale = 1);

    // description: Draws rectangle with gradient color.
    // return: void
    // precondition: Positive width & height.
    // postcondition: Gradient rectangle is drawn.
    void drawGradientRect(int x, int y, int w, int h, int r1, int g1, int b1, int r2, int g2, int b2);
    // description: Draws a circle at center (cx,cy).
    // return: void
    // precondition: radius > 0.
    // postcondition: Circle is drawn to screen.
    void drawCircle(int cx, int cy, int radius, int r, int g, int b);
    // description: Draws a filled rectangle (box).
    // return: void
    // precondition: w,h > 0.
    // postcondition: Box is drawn on screen.
    void drawBox(int x, int y, int w, int h, int r, int g, int b);

    // description: Draws background terrain with scrolling.
    // return: void
    // precondition: plotter running.
    // postcondition: Terrain displayed on screen.
    void drawTerrain(float bgScroll, float gameTime);
    // description: Draws simple building shape.
    // return: void
    // precondition: Valid dimensions.
    // postcondition: Building appears on screen.
    void drawBuilding(int x, int y, int w, int h, int r, int g, int b);

    // description: Draws player at lane and height.
    // return: void
    // precondition: currentLane within game lanes.
    // postcondition: Player sprite is shown.
    void drawPlayer(int currentLane, float playerY, float animTime);
    // description: Draws all obstacles.
    // return: void
    // precondition: obstacles vector initialized.
    // postcondition: Obstacles displayed.
    void drawObstacles(const std::vector<Obstacle>& obstacles);
    // description: Draws all collectibles.
    // return: void
    // precondition: collectibles vector valid.
    // postcondition: Collectibles rendered.
    void drawCollectibles(const std::vector<Collectible>& collectibles);
    // description: Draws particle effects.
    // return: void
    // precondition: particles vector valid.
    // postcondition: Particles rendered.
    void drawParticles(const std::vector<Particle>& particles);
    // description: Draws HUD with score/life info.
    // return: void
    // precondition: Valid game state values.
    // postcondition: HUD rendered on screen.
    void drawHUD(int score, int lives, int level, int comboMultiplier, float comboTimer,
                 bool showInstructions, float instructionTimer, int gameState);
    // description: Draws start screen UI.
    // return: void 
    // precondition: plotter active.
    // postcondition: Start screen visible.
    void drawStartScreen();
    // description: Draws game-over screen with score.
    // return: void
    // precondition: Valid score & level.
    // postcondition: Game-over screen displayed.
    void drawGameOverScreen(int score, int level);
    // description: Draws pause screen overlay.
    // return: void
    // precondition: plotter running.
    // postcondition: Pause screen shown.
    void drawPauseScreen();
};

#endif
