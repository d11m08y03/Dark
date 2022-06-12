#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector> 
#include <fstream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

void firstScene(RenderWindow* window, SDL_Event* event, bool* gameRunning, bool* levelRunning, int windowWidth, int windowHeight);