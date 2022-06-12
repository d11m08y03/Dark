#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Entity.hpp"
#include "Particles.hpp"

class RenderWindow{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<Particle> vectorOfParticle;

    SDL_Rect fontDestination;

public:
    // Constructor
    RenderWindow(const char* pTitle, int windowWidth, int windowHeight);

    // Methods for textures
    SDL_Texture* loadTexture(const char* pFilePath);
    void clearRenderer();
    void renderTexture(Entity& entity, float scaling);
    void renderTextureFromSheet(Entity& entity);
    void renderTextureFullScreen(Entity& entity);
    void updateRenderer();
    void cleanUp();

    // Methods for fonts
    void renderFont(Entity& entity, const char* message, int pX, int pY, char color);
    SDL_Rect getFontDimensions(Entity& entity, const char* message, int pX, int pY);

    // Methods for particles
    void generateParticles(int numberOfParticles, int xLimit, int yLimit);
    void renderParticles(int numberOfParticles, int xLimit, int yLimit);

    void renderRect(SDL_Rect rectangle, int alpha);
};