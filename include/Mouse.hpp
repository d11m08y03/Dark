#pragma once
#include <SDL2/SDL.h>
#include <iostream>

#include "Entity.hpp"
#include "RenderWindow.hpp"

class Mouse{
private:
    int mouseX, mouseY;

public:
    // Constructor
    Mouse();

    // Methods
    void updateMousePosition(int pMouseX, int pMouseY);
    bool checkForClick(SDL_Rect pFontCoordinate);
};