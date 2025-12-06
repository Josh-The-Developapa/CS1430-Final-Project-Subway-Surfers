#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

struct Obstacle {
    int lane;
    float y;
    int type;
    bool active;

    int getX() const;
    int getWidth() const;
    int getHeight() const;
};

struct Collectible {
    int lane;
    float y;
    int type;
    bool active;
    float animTime;

    int getX() const;
};

struct Particle {
    float x, y, vx, vy;
    int r, g, b;
    float life, maxLife;
    int size;
};

#endif