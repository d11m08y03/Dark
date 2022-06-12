#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <fstream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Mouse.hpp"
#include "Scenarios.hpp"

class Level{
private:
    int windowWidth, windowHeight;
    RenderWindow* window;
    bool* gameRunning;
    SDL_Event* event;

public:
    // Constructor
    Level(int pWindowWidth, int pWindowHeight, RenderWindow* pWindow, bool* pGameRunning, SDL_Event* pEvent);

    // Level rendering Methods
    void renderLevel1();
    void renderLevel2();
    void renderLevel3();

    bool detectCollisionY(SDL_Rect one, std::vector<Entity>);
    void pauseMenu(Entity& backgroundTextureEntity, bool* levelRunning);
    void gettingUserInput(Entity& backgroundTextureEntity, bool* levelRunning);
};