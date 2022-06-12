#include "Mouse.hpp"

Mouse::Mouse()
{

}

void Mouse::updateMousePosition(int pMouseX, int pMouseY)
{
    mouseX = pMouseX;
    mouseY = pMouseY;

    // std::cout << mouseX << "," << mouseY << std::endl;
}

bool Mouse::checkForClick(SDL_Rect pFontCoordinates)
{
    if(mouseX > pFontCoordinates.x && mouseX < (pFontCoordinates.x + pFontCoordinates.w)){
        if(mouseY > pFontCoordinates.y && mouseY < (pFontCoordinates.y + pFontCoordinates.h)){
            // std::cout << "Font pressed.";
            return true;
        }
    }
    return false;
}
