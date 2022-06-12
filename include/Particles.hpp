#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <random>

class Particle{
private:
    float x, y;
    float xDirection, yDirection;

public:
    // Constructor
    Particle(float pX, float pY, float pXDirection, float pYDirection);

    // Methods
    void generateParticles(int numberOfParticles, int xLimit, int yLimit);
    void update(int xLimit, int yLimit);
    int getX();
    int getY();
};