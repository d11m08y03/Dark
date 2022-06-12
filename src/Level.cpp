/*
Libraries in header file:
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Mouse.hpp"
*/
#include "Level.hpp"
#include "Entity.hpp"
#include "Mouse.hpp"
#include "Scenarios.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <iterator>
#include <libintl.h>
#include <locale>
#include <ostream>
#include <random>
#include <string>
#include <vector>

Level::Level(int pWindowWidth, int pWindowHeight, RenderWindow* pWindow, bool* pGameRunning, SDL_Event* pEvent)
:windowWidth(pWindowWidth), windowHeight(pWindowHeight), window(pWindow), gameRunning(pGameRunning), event(pEvent)
{

}

void Level::gettingUserInput(Entity& backgroundTextureEntity, bool* levelRunning)
{
    window->clearRenderer();

    Entity lineFont("res/Fonts/FreeSans.ttf", 50);

    SDL_Rect textBackground;
    textBackground.w = windowWidth - windowWidth / 6;
    textBackground.h = windowHeight / 6;
    textBackground.x = windowWidth / 12;
    textBackground.y = windowHeight - windowHeight / 5;
    int textBackgroundOffsetY = 1;

    std::string userInput = "";
    bool userInputRunning = true;
    while(userInputRunning){
        while(SDL_PollEvent(event)){
            switch (event->type) {
                case SDL_QUIT:
                    userInputRunning = false;
                    *levelRunning = false;
                    *gameRunning = false;
                    break;

                case SDL_KEYUP:
                    switch (event->key.keysym.sym) {
                        case SDLK_RETURN:
                            userInputRunning = false;
                            break;

                        case SDLK_BACKSPACE:
                            if(userInput != ""){
                                userInput.pop_back();
                            }
                            break;

                        default:
                            userInput += (char)(event->key.keysym.sym);
                            break;    
                    }
                    break;

                default:
                    break;
            }
        }

        window->clearRenderer();

        window->renderTextureFullScreen(backgroundTextureEntity);

        textBackground.y += textBackgroundOffsetY;
        if(textBackground.y > (windowHeight - windowHeight / 5) + 5 || textBackground.y < (windowHeight - windowHeight / 5) - 5){
            textBackgroundOffsetY = textBackgroundOffsetY * -1;
            textBackground.y += 2*textBackgroundOffsetY;
        }
        window->renderRect(textBackground, 200);

        window->renderFont(lineFont, userInput.c_str(), (windowWidth / 2) - 25, windowHeight - windowHeight / 6, 'w');

        window->updateRenderer();

    }
}

void Level::pauseMenu(Entity& backgroundTextureEntity, bool* levelRunning)
{
    window->clearRenderer();

    Mouse mouse;
    int mouseX = 0, mouseY = 0;

    Entity buttonFont("res/Fonts/italic.ttf", 50);

    const int RESUME_BUTTON_X = 410;
    const int EXIT_BUTTON_X = 710;
    int RESUME_BUTTON_Y = 225;
    int EXIT_BUTTON_Y = 225;
    int buttonOffsetY = -1;

    const int numberOfParticles = 100;
    window->generateParticles(numberOfParticles, windowWidth, windowHeight);

    SDL_Rect menuBackground;
    menuBackground.w = windowWidth;
    menuBackground.h = windowHeight;
    menuBackground.x = 0;
    menuBackground.y = 0;

    bool pauseMenuRunning = true;
    while(pauseMenuRunning){
        while(SDL_PollEvent(event)){
            switch(event->type){
                case SDL_QUIT:
                    pauseMenuRunning = false;
                    *levelRunning = false;
                    *gameRunning = false;

                case SDL_MOUSEBUTTONDOWN:
                    if(mouse.checkForClick(window->getFontDimensions(buttonFont, "Resume", RESUME_BUTTON_X, RESUME_BUTTON_Y))){
                        pauseMenuRunning = false;
                    }

                    if(mouse.checkForClick(window->getFontDimensions(buttonFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y))){
                        pauseMenuRunning = false;
                        *levelRunning = false;
                        *gameRunning = false;
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        mouse.updateMousePosition(mouseX, mouseY);

        window->clearRenderer();

        window->renderTextureFullScreen(backgroundTextureEntity);
        
        window->renderRect(menuBackground, 200);

        if(mouse.checkForClick(window->getFontDimensions(buttonFont, "Resume", RESUME_BUTTON_X, RESUME_BUTTON_Y))){
            RESUME_BUTTON_Y += buttonOffsetY;
            if(RESUME_BUTTON_Y > 230 || RESUME_BUTTON_Y < 220){
                RESUME_BUTTON_Y -= 2 * buttonOffsetY;
                buttonOffsetY = -1 * buttonOffsetY;
            }
            window->renderFont(buttonFont, "Resume", RESUME_BUTTON_X, RESUME_BUTTON_Y, 'w');
        }
        else{
            window->renderFont(buttonFont, "Resume", RESUME_BUTTON_X, RESUME_BUTTON_Y, '$');
        
        }
        if(mouse.checkForClick(window->getFontDimensions(buttonFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y))){
            EXIT_BUTTON_Y += buttonOffsetY;
            if(EXIT_BUTTON_Y > 230 || EXIT_BUTTON_Y < 220){
                EXIT_BUTTON_Y -= 2 * buttonOffsetY;
                buttonOffsetY = -1 * buttonOffsetY;
            }
            window->renderFont(buttonFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y, 'w');
        }
        else{
            window->renderFont(buttonFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y, '$');
        }


        window->renderParticles(numberOfParticles, windowWidth, windowHeight);

        window->updateRenderer();
    }
}

bool Level::detectCollisionY(SDL_Rect one, std::vector<Entity> platforms)
{   
    for(int i = 0; i < (int)platforms.size(); ++i){
        if(one.y  == platforms[i].getY() - one.h && one.x >= platforms[i].getX() && one.x <= platforms[i].getX() + platforms[i].getScaledWidth()){
            return true;
        }
    }

    return false;
}

void Level::renderLevel1()
{
    window->clearRenderer(); 

    SDL_Texture* prime = window->loadTexture("res/Images/Level0.jpg");
    SDL_Texture* background0Texture = window->loadTexture("res/stringstar-fields/background_0.png");
    SDL_Texture* background1Texture = window->loadTexture("res/stringstar-fields/background_1.png");
    SDL_Texture* background2Texture = window->loadTexture("res/stringstar-fields/background_2.png");
    
    SDL_Texture* tilesetTexture = window->loadTexture("res/stringstar-fields/tileset.png");

    Entity backgroundTextureEntity(0, 0, prime);
    Entity background0Entity(0, 0, background0Texture);

    Entity background1Entity(0, -140, background1Texture);
    Entity background1EntityShadow(windowWidth, -140, background1Texture);

    Entity background2Entity(0, -90, background2Texture);
    Entity background2EntityShadow(-1 * windowWidth, -90, background2Texture);

    std::vector<Entity> platforms;
    platforms.push_back(Entity(tilesetTexture, 80, 64, 80, 15, 0, 500, 5));
    platforms.push_back(Entity(tilesetTexture, 80, 64, 80, 15, 300, 400, 2));


    std::vector<Entity> backgroundObjects;
    // Small tree
    backgroundObjects.push_back(Entity(tilesetTexture, 6, 81, 50, 62, platforms[0].getX(), platforms[0].getY() - (62 * 3), 3));

    // Rock?
    backgroundObjects.push_back(Entity(tilesetTexture, 48, 59, 32, 21, platforms[0].getX() + 100, platforms[0].getY() - (21 * 2), 2));

    // Dangling shit
    backgroundObjects.push_back(Entity(tilesetTexture, 0 ,32, 15, 29, platforms[0].getX() + 150, platforms[0].getY() + platforms[0].getCurrentDimensions().h, 4));

    Entity buttonFont("res/Fonts/italic.ttf", 30);
    Entity lineFont("res/Fonts/FreeSans.ttf", 30);

    // Player
    SDL_Rect player;
    player.x = 0;
    player.y = 0;
    player.w = 10;
    player.h = 10;
    const int PLAYER_SPEED = 5;
    int GRAVITY = 5;
 
    Mouse mouse;
    int mouseX = 0, mouseY = 0;

    bool levelRunning = true;
    while(levelRunning){
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        while(SDL_PollEvent(event)){
            switch(event->type){
                case SDL_QUIT:
                    *gameRunning = false;
                    levelRunning = false;
                    break;

                case SDL_KEYUP:
                    if(event->key.keysym.sym == SDLK_i){
                        gettingUserInput(backgroundTextureEntity, &levelRunning);
                    }

                    if(event->key.keysym.sym == SDLK_SPACE){
                        for(int i = 0; i < 50; ++i){
                            player.y -= 1;
                            window->renderRect(player, -1);    
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(mouse.checkForClick(window->getFontDimensions(lineFont, "Pause", 50, 10))){
                        pauseMenu(backgroundTextureEntity, &levelRunning);
                    }
                    break;

                default:
                    break; 
            }
        }

        // Moving background "logic"
        background1Entity.updatePosition(-1, 0);
        background1EntityShadow.updatePosition(-1, 0);
        background2Entity.updatePosition(1, 0);
        background2EntityShadow.updatePosition(1, 0);

        if(background1Entity.getCurrentDimensions().x + background1Entity.getCurrentDimensions().w * 4 < 0){
            background1Entity.setPosition(windowWidth, -140);
        }

        if(background1EntityShadow.getCurrentDimensions().x + background1EntityShadow.getCurrentDimensions().w * 4 < 0){
            background1EntityShadow.setPosition(windowWidth, -140);
        }

        if(background2Entity.getCurrentDimensions().x > windowWidth){
            background2Entity.setPosition(-1 * windowWidth, -90);
        }

        if(background2EntityShadow.getCurrentDimensions().x > windowWidth){
            background2EntityShadow.setPosition(-1 * windowWidth, -90);
        }

        // Detecting keys pressed
        if(state[SDL_SCANCODE_BACKSPACE]){
            levelRunning = false;
        }

        if(state[SDL_SCANCODE_P]){
            pauseMenu(backgroundTextureEntity, &levelRunning);
        }

        // Player movement
        if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]){
            player.x += PLAYER_SPEED;
        }

        if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]){
            player.x -= PLAYER_SPEED;
        }

        if(!detectCollisionY(player, platforms)){
            player.y += GRAVITY;
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        mouse.updateMousePosition(mouseX, mouseY);

        // Clearing previous frame
        window->clearRenderer();

        // Render stuff
        window->renderTextureFullScreen(background0Entity);

        window->renderTexture(background1Entity, 4.0);
        window->renderTexture(background1EntityShadow, 4.0);
        window->renderTexture(background2Entity, 4.0);
        window->renderTexture(background2EntityShadow, 4.0);

        if(mouse.checkForClick(window->getFontDimensions(buttonFont, "Pause", 50, 10))){
            window->renderFont(buttonFont, "Pause", 50, 10, 'w');
        }
        else{
            window->renderFont(buttonFont, "Pause", 50, 10, '$');
        }

        for(int i = 0; i < (int)platforms.size(); ++i){
            window->renderTextureFromSheet(platforms[i]);
        }

        for(int i = 0; i < (int)backgroundObjects.size(); ++i){
            window->renderTextureFromSheet(backgroundObjects[i]);
        }

        window->renderFont(buttonFont, "Level 1", windowWidth / 2, 20, '$');

        window->renderRect(player, -1);
        // Update renderer
        window->updateRenderer();
    }
}

void Level::renderLevel2()
{
    window->clearRenderer();

    // Loading resources
    SDL_Texture* backgroundTexture = window->loadTexture("res/Images/Level1.jpg");

    Entity backgroundTextureEntity1(100, 100, backgroundTexture);
    Entity buttonFont("res/Fonts/FreeSans.ttf", 75);
    Entity scenarioFont("res/Fonts/italicBold.ttf", 50);
    const int PAUSE_BUTTON_X = 200;
    int PAUSE_BUTTON_Y = 200;
    int buttonOffsetY = 1;

    Mouse mouse;
    int mouseX, mouseY;

    // Background for lines
    SDL_Rect textBackground;
    textBackground.w = windowWidth - windowWidth / 6;
    textBackground.h = windowHeight / 6;
    textBackground.x = windowWidth / 12;
    textBackground.y = windowHeight - windowHeight / 5;
    int textBackgroundOffsetY = 1;

    bool levelRunning = true;
    while(levelRunning){
        while(SDL_PollEvent(event)){
            switch(event->type){
                case SDL_QUIT:
                    *gameRunning = false;
                    levelRunning = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    break;
                
                default:
                    break; 
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_BACKSPACE]){
            levelRunning = false;
        }

        if(state[SDL_SCANCODE_S]){
            firstScene(window, event, gameRunning, &levelRunning, windowWidth, windowHeight);
        }

        // Getting mouse coordinates
        SDL_GetMouseState(&mouseX, &mouseY);
        mouse.updateMousePosition(mouseX, mouseY);

        // Clearing previous frame
        window->clearRenderer();

        window->renderTextureFullScreen(backgroundTextureEntity1);

        window->renderFont(buttonFont, "Level 2", windowWidth / 2, 20, '$');
    
        if(mouse.checkForClick(window->getFontDimensions(buttonFont, "Pause", PAUSE_BUTTON_X, PAUSE_BUTTON_Y))){
            PAUSE_BUTTON_Y += buttonOffsetY;

            if(PAUSE_BUTTON_Y > 210 || PAUSE_BUTTON_Y < 190){
                PAUSE_BUTTON_Y -= 2 * buttonOffsetY;
                buttonOffsetY = -1 * buttonOffsetY;
            }
            window->renderFont(buttonFont, "Pause", PAUSE_BUTTON_X, PAUSE_BUTTON_Y, 'w');
        }
        else{
            window->renderFont(buttonFont, "Pause", PAUSE_BUTTON_X, PAUSE_BUTTON_Y, '$');
        }


        textBackground.y += textBackgroundOffsetY;
        if(textBackground.y > (windowHeight - windowHeight / 5) + 5 || textBackground.y < (windowHeight - windowHeight / 5) - 5){
            textBackgroundOffsetY = textBackgroundOffsetY * -1;
            textBackground.y += 2*textBackgroundOffsetY;
        }
        window->renderRect(textBackground, 200);

        // Update screen
        window->updateRenderer();
    }
}

void Level::renderLevel3()
{
    window->clearRenderer();

    SDL_Texture* backgroundTexture = window->loadTexture("res/Images/Level3.jpg");

    Entity backgroundTextureEntity1(100, 100, backgroundTexture);

    Entity buttonFont("res/Fonts/FreeSans.ttf", 125);

    window->clearRenderer();

    bool levelRunning = true;
    while(levelRunning){
        while(SDL_PollEvent(event)){
            switch(event->type){
                case SDL_QUIT:
                    *gameRunning = false;
                    levelRunning = false;
                    break;
                
                default:
                    break; 
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_BACKSPACE]){
            levelRunning = false;
        }

        window->clearRenderer();

        window->renderTextureFullScreen(backgroundTextureEntity1);

        window->renderFont(buttonFont, "Level 1", windowWidth / 2, 20, '$');

        window->updateRenderer();
    }
}
