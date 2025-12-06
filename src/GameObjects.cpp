#include "GameObjects.h"

#include "Constants.h"

int Obstacle::getX() const {
    return 225 + lane * 250;
}

int Obstacle::getWidth() const {
    return type == 1 ? 180 : 120;
}

int Obstacle::getHeight() const {
    return type == 1 ? 80 : 50;
}

int Collectible::getX() const {
    return 250 + lane * 250;
}