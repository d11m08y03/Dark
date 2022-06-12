#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Entity
{
private:
    SDL_Rect currentDimensions;
    SDL_Texture* texture;

    TTF_Font* font;

    float textureScaledWidth;
    float textureScaledHeight;
    int x, y;

public:
    // Constructors
    Entity(int x, int y, SDL_Texture* pTexture);
    Entity(const char* fontFilePath, int fontSize);
    Entity(SDL_Texture* pTexture, int textureX, int textureY, int pWidth, int pHeight, int pX, int pY, float scaling);

    // Methods for texture
    SDL_Texture* getTexture();
    SDL_Rect getCurrentDimensions();
    void updatePosition(int xMovement, int yMovement);
    void setPosition(int pX, int pY);
    float getScaledWidth();
    float getScaledHeight();
    int getX();
    int getY();

    // Methods for fonts
    TTF_Font* getFont();
};

