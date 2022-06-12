/*
Libraries in header file:
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
*/

#include "RenderWindow.hpp"
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

RenderWindow::RenderWindow(const char* windowTitle, int windowWidth, int windowHeight)
:window(NULL), renderer(NULL)
{
    // Creates a window
    window = SDL_CreateWindow(windowTitle, 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    windowWidth, windowHeight, 
    SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;
    }

    // Creates a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
        
    }
};

// Loads a texture onto the current window's renderer
SDL_Texture* RenderWindow::loadTexture(const char* textureFilePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, textureFilePath);
    if(texture == NULL)
    {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::clearRenderer()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::renderTexture(Entity& entity, float scaling)
{
    SDL_Rect textureDestination;
    textureDestination.x = entity.getCurrentDimensions().x;
    textureDestination.y = entity.getCurrentDimensions().y;
    SDL_QueryTexture(entity.getTexture(), NULL, NULL, &textureDestination.w, &textureDestination.h);
    textureDestination.w = textureDestination.w * scaling;
    textureDestination.h = textureDestination.h * scaling;

    SDL_RenderCopy(renderer, entity.getTexture(), NULL, &textureDestination);
}

void RenderWindow::renderTextureFromSheet(Entity &entity)
{
    SDL_Rect src = entity.getCurrentDimensions();

    SDL_Rect textureDestination;
    textureDestination.x = entity.getX();
    textureDestination.y = entity.getY();
    textureDestination.w = entity.getScaledWidth();
    textureDestination.h = entity.getScaledHeight();

    SDL_RenderCopy(renderer, entity.getTexture(), &src, &textureDestination);
}

void RenderWindow::renderTextureFullScreen(Entity& entity)
{
    SDL_RenderCopy(renderer, entity.getTexture(), NULL, NULL);
}

void RenderWindow::renderFont(Entity& entity, const char* message, int pX, int pY, char color)
{
    SDL_Color fontColor;
    if(color != '$'){
        switch (color) {
            case 'w':
                fontColor = {255, 255, 255};
                break;

            default:
                break;
        }
    }
    else{
        fontColor = {0, 0, 0};
    }

    SDL_Surface* fontSurface = TTF_RenderText_Blended(entity.getFont(), message, fontColor);
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);

    SDL_QueryTexture(fontTexture, NULL, NULL, &fontDestination.w, &fontDestination.h);
    fontDestination.x = pX - (fontDestination.w / 2);
    fontDestination.y = pY;

    SDL_RenderCopy(renderer, fontTexture, NULL, &fontDestination);

    SDL_DestroyTexture(fontTexture);
}

SDL_Rect RenderWindow::getFontDimensions(Entity& entity, const char* message, int pX, int pY)
{
    SDL_Surface* fontSurface = TTF_RenderText_Blended(entity.getFont(), message, {0, 0, 0});
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);

    SDL_Rect fontDimentions;
    SDL_QueryTexture(fontTexture, NULL, NULL, &fontDimentions.w, &fontDimentions.h);
    fontDimentions.x = pX - (fontDimentions.w / 2);
    fontDimentions.y = pY;

    SDL_DestroyTexture(fontTexture);

    return fontDimentions;
}

void RenderWindow::generateParticles(int numberOfParticles, int xLimit, int yLimit)
{
    for(int i = 0; i < numberOfParticles; i++){
        vectorOfParticle.push_back(
            Particle(
                rand() % xLimit, 
                rand() % yLimit, 
                rand() % 10, 
                rand() % 10 
            )
        );
    }
}

void RenderWindow::renderParticles(int numberOfParticles, int xLimit, int yLimit)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i = 0; i < numberOfParticles; i++){
        SDL_Rect temp;
        temp.x = vectorOfParticle[i].getX();
        temp.y = vectorOfParticle[i].getY();
        temp.w = 3;
        temp.h = 3;

        SDL_RenderFillRect(renderer, &temp);

        vectorOfParticle[i].update(xLimit, yLimit);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

void RenderWindow::renderRect(SDL_Rect rectangle, int alpha)
{   
    if(alpha != -1){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
}

void RenderWindow::updateRenderer()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}