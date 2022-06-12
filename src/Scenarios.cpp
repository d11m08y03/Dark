/*
Libraries in header file:
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "RenderWindow.hpp"
*/

#include "Scenarios.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <cstdio>
#include <vector>

void firstScene(RenderWindow *window, SDL_Event *event, bool *gameRunning, bool *levelRunning, int windowWidth, int windowHeight)
{
	SDL_Texture* backgroundTexture = window->loadTexture("res/Images/Level0.jpg");
	
	Entity backgroundEntity(0, 0, backgroundTexture);

	Entity lineFont("res/Fonts/italicBold.ttf", 25);

	SDL_Rect linesBackground;
	linesBackground.x = windowWidth / 12;
	linesBackground.y = windowHeight - windowHeight / 5;
	linesBackground.w = windowWidth - windowWidth / 6;
	linesBackground.h = windowHeight / 6;

	std::vector<std::string> lines;
	std::fstream scenarioFile;
	scenarioFile.open("res/Scenarios/scenario1.txt", std::ios::in);
	if(scenarioFile.is_open()){
		std::string line;
		while(getline(scenarioFile, line)){
			lines.push_back(line);
		}

		scenarioFile.close();
	} 
	else{
		std::cout << "File could not be opened." << std::endl;
	}
	int lineCount = 0;

	bool scenarioRunning = true;
	while(scenarioRunning){
		while(SDL_PollEvent(event)){
			switch(event->type){
				case SDL_QUIT:
					scenarioRunning = false;
					*levelRunning = false;
					*gameRunning = false;
					break;

				case SDL_KEYUP:
					if(event->key.keysym.sym == SDLK_BACKSPACE){
						scenarioRunning = false;
					}

					if(event->key.keysym.sym == SDLK_RETURN){
						if(lineCount != lines.size() - 1){
							lineCount += 1;
						}
						else{
							lineCount = 0;
						}
					}
				
				default:
					break;
			}		
		}

		// Clearing previous frame
		window->clearRenderer();

		// Rendering stuff
		window->renderTextureFullScreen(backgroundEntity);

		window->renderRect(linesBackground, 200);

		window->renderFont(lineFont, lines[lineCount].c_str(), (windowWidth / 2), windowHeight - windowHeight / 6, 'w');

		// Updating screen
		window->updateRenderer();
	}
}