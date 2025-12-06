#include "Renderer.h"

#include <cmath>
#include <cstdlib>

#include "Constants.h"

Renderer::Renderer(SDL_Plotter& g, int w, int h)
    : plotter(g), screenWidth(w), screenHeight(h) {}

void Renderer::drawChar(int x, int y, char c, int r, int g, int b, int scale) {
    c = toupper(c);
    if (FONT_5X7.find(c) == FONT_5X7.end()) return;

    std::vector<int>& charData = FONT_5X7[c];
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 8; col++) {
            if (charData[row] & (1 << (7 - col))) {
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        int px = x + col * scale + sx;
                        int py = y + row * scale + sy;
                        if (px >= 0 && px < screenWidth && py >= 0 && py < screenHeight) {
                            plotter.plotPixel(px, py, r, g, b);
                        }
                    }
                }
            }
        }
    }
}

void Renderer::drawText(int x, int y, const std::string& text, int r, int g, int b, int scale) {
    int currentX = x;
    for (char c : text) {
        drawChar(currentX, y, c, r, g, b, scale);
        currentX += 8 * scale + scale;
    }
}

void Renderer::drawTextCentered(int y, const std::string& text, int r, int g, int b, int scale) {
    int textWidth = text.length() * (8 * scale + scale);
    int x = (screenWidth - textWidth) / 2;
    drawText(x, y, text, r, g, b, scale);
}

void Renderer::drawTextWithShadow(int x, int y, const std::string& text, int r, int g, int b, int scale) {
    drawText(x + 2, y + 2, text, 0, 0, 0, scale);
    drawText(x, y, text, r, g, b, scale);
}

void Renderer::drawTextCenteredWithShadow(int y, const std::string& text, int r, int g, int b, int scale) {
    int textWidth = text.length() * (8 * scale + scale);
    int x = (screenWidth - textWidth) / 2;
    drawTextWithShadow(x, y, text, r, g, b, scale);
}

void Renderer::drawGradientRect(int x, int y, int w, int h, int r1, int g1, int b1, int r2, int g2, int b2) {
    for (int py = 0; py < h; py++) {
        float ratio = (float)py / h;
        int r = r1 + (int)((r2 - r1) * ratio);
        int g = g1 + (int)((g2 - g1) * ratio);
        int b = b1 + (int)((b2 - b1) * ratio);

        for (int px = 0; px < w; px++) {
            if (x + px >= 0 && x + px < screenWidth && y + py >= 0 && y + py < screenHeight) {
                plotter.plotPixel(x + px, y + py, r, g, b);
            }
        }
    }
}

void Renderer::drawCircle(int cx, int cy, int radius, int r, int g, int b) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = cx + x;
                int py = cy + y;
                if (px >= 0 && px < screenWidth && py >= 0 && py < screenHeight) {
                    plotter.plotPixel(px, py, r, g, b);
                }
            }
        }
    }
}

void Renderer::drawBox(int x, int y, int w, int h, int r, int g, int b) {
    drawGradientRect(x, y, w, h, r, g, b, r - 10, g - 10, b - 10);

    for (int i = 0; i < w; i++) {
        plotter.plotPixel(x + i, y, 200, 200, 150);
        plotter.plotPixel(x + i, y + h - 1, 200, 200, 150);
    }
    for (int i = 0; i < h; i++) {
        plotter.plotPixel(x, y + i, 200, 200, 150);
        plotter.plotPixel(x + w - 1, y + i, 200, 200, 150);
    }
}

void Renderer::drawBuilding(int x, int y, int w, int h, int r, int g, int b) {
    if (x + w < 0 || x > screenWidth) return;

    drawGradientRect(x, y, w, h, r, g, b, r - 10, g - 10, b - 10);

    for (int wy = y + 10; wy < y + h - 10; wy += 25) {
        for (int wx = x + 10; wx < x + w - 10; wx += 20) {
            bool lit = (rand() % 3 != 0);
            int brightness = lit ? 255 : 50;
            drawGradientRect(wx, wy, 12, 15, brightness, brightness, 100,
                             brightness - 50, brightness - 50, 50);
        }
    }
}

void Renderer::drawTerrain(float bgScroll, float gameTime) {
    for (int y = 0; y < 250; y++) {
        float ratio = (float)y / 250;
        int r = (int)(100 + ratio * 30 + sin(gameTime * 0.5f) * 10);
        int g = (int)(180 + ratio * 40);
        int b = (int)(255 - ratio * 50);

        for (int x = 0; x < screenWidth; x++) {
            plotter.plotPixel(x, y, r, g, b);
        }
    }

    int buildingOffset = (int)(bgScroll * 0.3f) % 200;
    drawBuilding(50 - buildingOffset, 80, 120, 150, 40, 50, 70);
    drawBuilding(250 - buildingOffset, 120, 100, 100, 35, 45, 65);
    drawBuilding(500 - buildingOffset, 70, 140, 180, 45, 55, 75);
    drawBuilding(750 - buildingOffset, 100, 130, 140, 38, 48, 68);
    drawBuilding(950 - buildingOffset, 90, 110, 160, 42, 52, 72);

    drawGradientRect(0, 250, screenWidth, screenHeight - 250, 60, 65, 80, 90, 95, 120);

    int lineOffset = (int)bgScroll % 100;
    for (int y = 250 + lineOffset; y < screenHeight; y += 100) {
        for (int x = 0; x < screenWidth; x++) {
            if (x % 20 < 10) {
                plotter.plotPixel(x, y, 150, 150, 50);
            }
        }
    }

    int laneX[] = {225, 475, 725};
    for (int lx : laneX) {
        for (int y = 250; y < screenHeight; y++) {
            plotter.plotPixel(lx - 1, y, 150, 150, 70);
            plotter.plotPixel(lx, y, 220, 220, 120);
            plotter.plotPixel(lx + 1, y, 150, 150, 70);
        }
    }
}

void Renderer::drawPlayer(int currentLane, float playerY, float animTime) {
    int targetX = 250 + currentLane * 250;
    int playerX = targetX;
    int py = (int)playerY;

    int shadowY = 520;
    float shadowScale = 1.0f - (520 - py) / 200.0f;
    if (shadowScale > 0) {
        for (int sy = 0; sy < 8 * shadowScale; sy++) {
            for (int sx = -20 * shadowScale; sx < 20 * shadowScale; sx++) {
                plotter.plotPixel(playerX + 20 + sx, shadowY + sy, 0, 0, 0);
            }
        }
    }

    drawGradientRect(playerX, py, 40, 50, 0, 220, 255, 0, 150, 200);
    drawCircle(playerX + 20, py - 15, 18, 255, 180, 100);

    int eyeOffset = (int)(sin(animTime * 8) * 2);
    drawCircle(playerX + 12, py - 15 + eyeOffset, 3, 0, 0, 0);
    drawCircle(playerX + 28, py - 15 + eyeOffset, 3, 0, 0, 0);

    for (int i = -5; i <= 5; i++) {
        int smileY = py - 8 + abs(i) / 3;
        plotter.plotPixel(playerX + 20 + i, smileY, 0, 0, 0);
    }

    int legAnim = (int)(sin(animTime * 15) * 10);
    drawGradientRect(playerX + 8, py + 50, 10, 20 + abs(legAnim), 100, 50, 150, 80, 30, 120);
    drawGradientRect(playerX + 22, py + 50, 10, 20 + abs(-legAnim), 100, 50, 150, 80, 30, 120);

    int armAnim = (int)(sin(animTime * 15) * 8);
    drawGradientRect(playerX - 5, py + 10 + armAnim, 8, 25, 0, 200, 230, 0, 150, 180);
    drawGradientRect(playerX + 37, py + 10 - armAnim, 8, 25, 0, 200, 230, 0, 150, 180);
}

void Renderer::drawObstacles(const std::vector<Obstacle>& obstacles) {
    for (const auto& obs : obstacles) {
        if (!obs.active) continue;

        int x = obs.getX();
        int y = (int)obs.y;
        int w = obs.getWidth();
        int h = obs.getHeight();

        if (y < -100 || y > screenHeight + 100) continue;

        if (obs.type == 0) {
            drawGradientRect(x, y, w, h, 220, 80, 80, 180, 40, 40);
            for (int i = 0; i < w; i += 20) {
                drawGradientRect(x + i, y, 10, h, 255, 255, 0, 200, 200, 0);
            }
        } else if (obs.type == 1) {
            drawGradientRect(x - 30, y, w, h, 80, 180, 220, 40, 120, 180);
            for (int i = 10; i < w - 10; i += 35) {
                drawGradientRect(x - 30 + i, y + 10, 25, 30, 200, 230, 255, 150, 180, 200);
            }
        } else {
            drawGradientRect(x, y, w, h, 100, 200, 100, 60, 150, 60);
        }

        for (int i = 0; i < w; i++) {
            plotter.plotPixel(x + i, y + 2, 255, 255, 255);
        }
    }
}

void Renderer::drawCollectibles(const std::vector<Collectible>& collectibles) {
    for (const auto& col : collectibles) {
        if (!col.active) continue;

        int x = col.getX();
        int y = (int)col.y;

        if (y < -50 || y > screenHeight + 50) continue;

        float bounce = sin(col.animTime * 8) * 5;
        int cy = y + (int)bounce;

        if (col.type == 0) {
            drawCircle(x, cy, 15, 255, 215, 0);
            drawCircle(x, cy, 10, 255, 255, 100);
            drawCircle(x, cy, 5, 255, 255, 200);
        } else {
            drawCircle(x - 8, cy - 5, 8, 255, 50, 100);
            drawCircle(x + 8, cy - 5, 8, 255, 50, 100);
            for (int dy = 0; dy < 15; dy++) {
                int width = 16 - dy;
                for (int dx = -width / 2; dx < width / 2; dx++) {
                    plotter.plotPixel(x + dx, cy + dy, 255, 50, 100);
                }
            }
        }
    }
}

void Renderer::drawParticles(const std::vector<Particle>& particles) {
    for (const auto& p : particles) {
        if (p.life <= 0) continue;

        int x = (int)p.x;
        int y = (int)p.y;

        if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight) continue;

        float alpha = p.life / p.maxLife;
        int r = (int)(p.r * alpha);
        int g = (int)(p.g * alpha);
        int b = (int)(p.b * alpha);

        for (int dy = 0; dy < p.size; dy++) {
            for (int dx = 0; dx < p.size; dx++) {
                plotter.plotPixel(x + dx, y + dy, r, g, b);
            }
        }
    }
}

void Renderer::drawHUD(int score, int lives, int level, int comboMultiplier, float comboTimer,
                       bool showInstructions, float instructionTimer, int gameState) {
    drawBox(10, 10, 200, 60, 30, 40, 60);
    drawTextWithShadow(20, 20, "SCORE", 255, 200, 100, 1);
    drawTextWithShadow(20, 35, std::to_string(score), 255, 255, 150, 2);

    drawBox(350, 10, 200, 60, 30, 40, 60);
    drawTextWithShadow(360, 25, "LIVES:", 255, 100, 100, 1);
    for (int i = 0; i < lives; i++) {
        drawCircle(440 + i * 30, 40, 8, 255, 50, 100);
    }

    drawBox(690, 10, 200, 60, 30, 40, 60);
    drawTextWithShadow(700, 20, "LEVEL", 100, 200, 255, 1);
    drawTextWithShadow(700, 35, std::to_string(level), 150, 220, 255, 2);

    if (comboMultiplier > 1 && comboTimer > 0) {
        int comboY = 80;
        drawBox(350, comboY, 220, 40, 50, 20, 70);
        drawTextWithShadow(365, comboY + 10, "COMBO x" + std::to_string(comboMultiplier),
                           255, 100, 255, 2);
    }

    if (showInstructions && gameState == 1 && instructionTimer < 8.0f) {
        int alpha = 255;
        if (instructionTimer > 6.0f) {
            alpha = (int)(255 * (1.0f - (instructionTimer - 6.0f) / 2.0f));
        }

        drawBox(150, 140, 700, 120, 20, 20, 40);
        int r = (255 * alpha) / 255;
        int g = (200 * alpha) / 255;
        int b = (100 * alpha) / 255;

        drawTextCenteredWithShadow(155, "CONTROLS", r, g, b, 2);
        drawTextCenteredWithShadow(185, "A/LEFT - MOVE LEFT", r - 50, g - 50, b + 100, 1);
        drawTextCenteredWithShadow(205, "D/RIGHT - MOVE RIGHT", r - 50, g - 50, b + 100, 1);
        drawTextCenteredWithShadow(225, "W/UP/SPACE - JUMP", r - 50, g - 50, b + 100, 1);
        drawTextCenteredWithShadow(245, "P - PAUSE", r - 50, g - 50, b + 100, 1);
    }
}

void Renderer::drawStartScreen() {
    drawTerrain(0, 0);

    drawBox(100, 80, 800, 440, 30, 20, 60);
    drawTextCenteredWithShadow(110, "SUBWAY SURFER", 255, 200, 50, 4);
    drawTextCenteredWithShadow(200, "HOW TO PLAY", 100, 255, 200, 2);
    drawTextCenteredWithShadow(240, "USE A/D OR ARROW KEYS TO SWITCH LANES", 200, 200, 200, 1);
    drawTextCenteredWithShadow(260, "USE W/UP/SPACE TO JUMP OVER OBSTACLES", 200, 200, 200, 1);
    drawTextCenteredWithShadow(280, "COLLECT COINS FOR POINTS", 255, 215, 0, 1);
    drawTextCenteredWithShadow(300, "COLLECT HEARTS FOR EXTRA LIVES", 255, 100, 100, 1);
    drawTextCenteredWithShadow(320, "AVOID BARRIERS TRAINS AND SIGNS", 220, 100, 100, 1);
    drawTextCenteredWithShadow(340, "BUILD COMBOS BY COLLECTING COINS", 255, 150, 255, 1);
    drawTextCenteredWithShadow(380, "PRESS SPACE TO START", 100, 255, 100, 2);
    drawTextCenteredWithShadow(415, "PRESS P TO PAUSE    Q TO QUIT", 150, 150, 200, 1);

    drawCircle(350, 300, 15, 255, 215, 0);
    drawCircle(650, 320, 8, 255, 50, 100);
}

void Renderer::drawGameOverScreen(int score, int level) {
    drawBox(100, 150, 800, 300, 50, 30, 80);
    drawTextCenteredWithShadow(180, "GAME OVER!", 255, 100, 50, 3);
    drawTextCenteredWithShadow(250, "FINAL SCORE: " + std::to_string(score), 255, 200, 100, 2);
    drawTextCenteredWithShadow(290, "LEVEL REACHED: " + std::to_string(level), 100, 200, 255, 2);
    drawTextCenteredWithShadow(350, "PRESS R TO RESTART", 100, 255, 100, 2);
    drawTextCenteredWithShadow(385, "PRESS Q TO QUIT", 200, 200, 255, 1);
}

void Renderer::drawPauseScreen() {
    for (int y = 200; y < 400; y++) {
        for (int x = 250; x < 750; x++) {
            if ((x + y) % 4 == 0) {
                plotter.plotPixel(x, y, 0, 0, 0);
            }
        }
    }
    drawBox(250, 200, 500, 200, 40, 30, 70);
    drawTextCenteredWithShadow(230, "PAUSED", 100, 200, 255, 3);
    drawTextCenteredWithShadow(300, "PRESS P TO RESUME", 200, 200, 255, 2);
    drawTextCenteredWithShadow(340, "PRESS Q TO QUIT", 150, 150, 200, 1);
}