/*
Libraries in header file
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
*/
#include "Entity.hpp"
#include <SDL2/SDL_render.h>

// Constructors for textures
Entity::Entity(int pX, int pY, SDL_Texture* pTexture)
:texture(pTexture)
{
    currentDimensions.x = pX;
    currentDimensions.y = pY;
    SDL_QueryTexture(texture, NULL, NULL, &currentDimensions.w, &currentDimensions.h);
}

Entity::Entity(SDL_Texture* pTexture, int textureX, int textureY, int pWidth, int pHeight, int pX, int pY, float scaling)
:texture(pTexture), textureScaledWidth(pWidth * scaling), textureScaledHeight(pHeight * scaling)
{   
    currentDimensions.x = textureX;
    currentDimensions.y = textureY;
    currentDimensions.w = pWidth;
    currentDimensions.h = pHeight;

    x = pX;
    y = pY;
}

// Constructor for fonts
Entity::Entity(const char* fontFilePath, int fontSize)
{
    font = TTF_OpenFont(fontFilePath, fontSize);
}

// Methods for textures
SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentDimensions()
{
    return currentDimensions;
}

void Entity::updatePosition(int xMovement, int yMovement)
{
    currentDimensions.x += xMovement;
    currentDimensions.y += yMovement;
}

void Entity::setPosition(int pX, int pY)
{
    currentDimensions.x = pX;
    currentDimensions.y = pY;
}

float Entity::getScaledWidth()
{
    return textureScaledWidth;
}

float Entity::getScaledHeight()
{
    return textureScaledHeight;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}
// Methods for font
TTF_Font* Entity::getFont()
{
    return font;
}