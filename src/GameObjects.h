#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

struct Obstacle {
    int lane;
    float y;
    int type;
    bool active;

    //description: Get x coordinate of obstacle
    //return: int
    //precondition: x coordinate of obstacle exist
    //postcondition: x coordinate of obstacle is not modified
    int getX() const;

    //description: Get width of obstacle
    //return: int
    //precondition: Width of obstacle exists
    //postcondition: width of obstacle is not modified
    int getWidth() const;

    //description: Get height of obstacle
    //return: int
    //precondition: Height of obstacle exists
    //postcondition: height of obstacle is not modified
    int getHeight() const;
};

struct Collectible {
    int lane;
    float y;
    int type;
    bool active;
    float animTime;

    //description: Get x coordinate of collectible
    //return: int
    //precondition: x coordinate of collectible exists
    //postcondition: x coordinate of obstacle is not modified
    int getX() const;
};

struct Particle {
    float x, y, vx, vy;
    int r, g, b;
    float life, maxLife;
    int size;
};

#endif
