#include "Game.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Constants.h"

SubwaySurferGame::SubwaySurferGame(SDL_Plotter& g)
    : plotter(g),
      renderer(g, SCREEN_WIDTH, SCREEN_HEIGHT),
      screenWidth(SCREEN_WIDTH),
      screenHeight(SCREEN_HEIGHT),
      currentLane(1),
      playerY(PLAYER_Y_GROUND),
      verticalVelocity(0),
      isJumping(false),
      animTime(0),
      score(0),
      lives(3),
      level(1),
      gameTime(0),
      scrollSpeed(BASE_SCROLL_SPEED),
      gameState(STATE_START),
      bgScroll(0),
      comboMultiplier(1),
      comboTimer(0),
      showInstructions(true),
      instructionTimer(0),
      bgMusic(nullptr) {
    srand(time(NULL));
    spawnInitialObstacles();

    bgMusic = Mix_LoadMUS("./assets/memphis-trap-wav-349366.mp3");
    if (bgMusic == nullptr) {
        std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
    } else {
        Mix_PlayMusic(bgMusic, -1);
        Mix_VolumeMusic(64);
    }
}

SubwaySurferGame::~SubwaySurferGame() {
    if (bgMusic != nullptr) {
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
    }
}

void SubwaySurferGame::spawnInitialObstacles() {
    obstacles.clear();
    collectibles.clear();

    for (int i = 0; i < 10; i++) {
        if (rand() % 3 == 0) {
            Obstacle obs;
            obs.lane = rand() % NUM_LANES;
            obs.y = -i * 180.0f;
            obs.type = rand() % 3;
            obs.active = true;
            obstacles.push_back(obs);
        }

        if (rand() % 2 == 0) {
            Collectible col;
            col.lane = rand() % NUM_LANES;
            col.y = -i * 180.0f - 90;
            col.type = (rand() % 10 == 0) ? 1 : 0;
            col.active = true;
            col.animTime = 0;
            collectibles.push_back(col);
        }
    }
}

void SubwaySurferGame::spawnParticles(int x, int y, int count, int r, int g, int b) {
    for (int i = 0; i < count; i++) {
        Particle p;
        p.x = x;
        p.y = y;
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        float speed = 2 + rand() % 5;
        p.vx = cos(angle) * speed;
        p.vy = sin(angle) * speed - 3;
        p.r = r + (rand() % 50) - 25;
        p.g = g + (rand() % 50) - 25;
        p.b = b + (rand() % 50) - 25;
        p.life = p.maxLife = 1.0f + (rand() % 100) / 100.0f;
        p.size = 2 + rand() % 3;
        particles.push_back(p);
    }
}

void SubwaySurferGame::update(char key) {
    float dt = 0.016f;

    if (gameState == STATE_START) {
        if (key == ' ' || key == 's') {
            gameState = STATE_PLAYING;
            instructionTimer = 0;
        }
        if (key == 'q') {
            plotter.setQuit(true);
        }
        return;
    }

    if (key == 'q') {
        plotter.setQuit(true);
    }

    if (gameState == STATE_GAME_OVER) {
        if (key == 'r') {
            resetGame();
        }
        return;
    }

    if (key == 'p') {
        gameState = (gameState == STATE_PLAYING) ? STATE_PAUSED : STATE_PLAYING;
    }

    if (gameState != STATE_PLAYING) return;

    instructionTimer += dt;

    if ((key == 'a' || key == LEFT_ARROW) && currentLane > 0) {
        currentLane--;
    }
    if ((key == 'd' || key == RIGHT_ARROW) && currentLane < NUM_LANES - 1) {
        currentLane++;
    }
    if ((key == 'w' || key == UP_ARROW || key == ' ') && !isJumping) {
        verticalVelocity = JUMP_VELOCITY;
        isJumping = true;
        spawnParticles(250 + currentLane * LANE_SPACING, playerY + 70, 10, 200, 200, 255);
    }

    gameTime += dt;
    animTime += dt;
    bgScroll += scrollSpeed;

    if (comboTimer > 0) {
        comboTimer -= dt;
        if (comboTimer <= 0) {
            comboMultiplier = 1;
        }
    }

    if (isJumping) {
        verticalVelocity += GRAVITY;
        playerY += verticalVelocity;

        if (playerY >= PLAYER_Y_GROUND) {
            playerY = PLAYER_Y_GROUND;
            isJumping = false;
            verticalVelocity = 0;
        }
    }

    for (auto& obs : obstacles) {
        if (!obs.active) continue;

        obs.y += scrollSpeed;

        if (obs.y > screenHeight + 100) {
            obs.y = -100 - rand() % 200;
            obs.lane = rand() % NUM_LANES;
            obs.type = rand() % 3;
            score += 5 * comboMultiplier;
        }

        if (currentLane == obs.lane) {
            int playerBottom = (int)playerY + 70;
            int playerTop = (int)playerY;
            int obsBottom = (int)obs.y + obs.getHeight();
            int obsTop = (int)obs.y;

            if (playerBottom > obsTop && playerTop < obsBottom) {
                lives--;
                comboMultiplier = 1;
                comboTimer = 0;
                spawnParticles(250 + currentLane * LANE_SPACING, playerY, 30, 255, 100, 100);

                if (lives <= 0) {
                    gameState = STATE_GAME_OVER;
                }
                obs.y = -100 - rand() % 200;
            }
        }
    }

    for (auto& col : collectibles) {
        if (!col.active) continue;

        col.y += scrollSpeed;
        col.animTime += dt;

        if (col.y > screenHeight + 50) {
            col.y = -50 - rand() % 300;
            col.lane = rand() % NUM_LANES;
            col.type = (rand() % 15 == 0) ? 1 : 0;
            col.active = true;
        }

        if (currentLane == col.lane) {
            int dist = abs((int)col.y - (int)playerY);
            if (dist < 40) {
                col.active = false;
                if (col.type == 0) {
                    score += 10 * comboMultiplier;
                    comboMultiplier++;
                    comboTimer = 3.0f;
                    spawnParticles(col.getX(), (int)col.y, 15, 255, 215, 0);
                } else {
                    lives = std::min(lives + 1, 5);
                    spawnParticles(col.getX(), (int)col.y, 20, 255, 50, 100);
                }
                col.y = -50 - rand() % 300;
                col.active = true;
            }
        }
    }

    for (auto& p : particles) {
        p.x += p.vx;
        p.y += p.vy;
        p.vy += 0.2f;
        p.life -= dt;
    }

    scrollSpeed = BASE_SCROLL_SPEED + level * 0.5f;
    if (score > level * 100) {
        level++;
    }
}

void SubwaySurferGame::resetGame() {
    score = 0;
    lives = 3;
    level = 1;
    gameTime = 0;
    scrollSpeed = BASE_SCROLL_SPEED;
    currentLane = 1;
    playerY = PLAYER_Y_GROUND;
    isJumping = false;
    verticalVelocity = 0;
    comboMultiplier = 1;
    comboTimer = 0;
    gameState = STATE_PLAYING;
    instructionTimer = 0;
    particles.clear();
    spawnInitialObstacles();
}

void SubwaySurferGame::render() {
    if (gameState == STATE_START) {
        renderer.drawStartScreen();
        return;
    }

    renderer.drawTerrain(bgScroll, gameTime);
    renderer.drawObstacles(obstacles);
    renderer.drawCollectibles(collectibles);
    renderer.drawPlayer(currentLane, playerY, animTime);
    renderer.drawParticles(particles);
    renderer.drawHUD(score, lives, level, comboMultiplier, comboTimer,
                     showInstructions, instructionTimer, gameState);

    if (gameState == STATE_PAUSED) {
        renderer.drawPauseScreen();
    } else if (gameState == STATE_GAME_OVER) {
        renderer.drawGameOverScreen(score, level);
    }
}