#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <ostream>

#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "Level.hpp"
#include "Sound.hpp"

int main(){
    // Initialisation
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        std::cout << "SDL_Init has failed. Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if(!(IMG_Init(IMG_INIT_JPG)) || !(IMG_Init(IMG_INIT_JPG))){
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if(TTF_Init() == -1){
        std::cout << "TTF_Init has failed. Error: " << TTF_GetError() << std::endl;
        return 1;
    } 

    const int WINDOW_SCALE_FACTOR = 70;
    const int WINDOW_WIDTH = 16 * WINDOW_SCALE_FACTOR;
    const int WINDOW_HEIGHT = 9 * WINDOW_SCALE_FACTOR;
    RenderWindow window("Stuff", WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Texture* backgroundTexture = window.loadTexture("res/Images/Level0.jpg");

    Entity backgroundTextureEntity(100, 100, backgroundTexture);

    Entity titleFont("res/Fonts/Airstone.ttf", 125);
    Entity normalFont("res/Fonts/italicBold.ttf", 50);

    const int TITLE_X = WINDOW_WIDTH / 2, TITLE_Y = 20;
    const int PLAY_BUTTON_X = 410;
    const int EXIT_BUTTON_X = 710;
    int PLAY_BUTTON_Y = 225;
    int EXIT_BUTTON_Y = 225;
    int buttonOffsetY = -1;

    // Particles
    const int numberOfParticles = 100;
    window.generateParticles(numberOfParticles, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Handling mouse
    int mouseX = 0, mouseY = 0;
    Mouse myMouse;

    // Sound
    // Sound sound;
    // sound.openAudioChannels();
    // sound.playMusic("res/Sounds/Blood.wav");

    bool gameRunning = true;
    SDL_Event event;
    Level levelmanager(WINDOW_WIDTH, WINDOW_HEIGHT, &window, &gameRunning, &event);

    while(gameRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    gameRunning = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(myMouse.checkForClick(window.getFontDimensions(normalFont, "Play", PLAY_BUTTON_X, PLAY_BUTTON_Y))){
                        levelmanager.renderLevel1();
                    }

                    if(myMouse.checkForClick(window.getFontDimensions(normalFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y))){
                        gameRunning = false;
                    }
                    break;

                default:
                    break;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE]){
            gameRunning = false;
        }

        if(state[SDL_SCANCODE_1]){
            levelmanager.renderLevel1();
        }

        if(state[SDL_SCANCODE_2]){
            levelmanager.renderLevel2();
        }

        if(state[SDL_SCANCODE_3]){
            levelmanager.renderLevel3();
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        myMouse.updateMousePosition(mouseX, mouseY);

        window.clearRenderer();

        window.renderTextureFullScreen(backgroundTextureEntity);

        if(myMouse.checkForClick(window.getFontDimensions(normalFont, "Play", PLAY_BUTTON_X, PLAY_BUTTON_Y))){
            PLAY_BUTTON_Y += buttonOffsetY;
            if(PLAY_BUTTON_Y > 230 || PLAY_BUTTON_Y < 220){
                PLAY_BUTTON_Y -= 2 * buttonOffsetY;
                buttonOffsetY = -1 * buttonOffsetY;
            }
            window.renderFont(normalFont, "Play", PLAY_BUTTON_X, PLAY_BUTTON_Y, 'w');
        }
        else{
            window.renderFont(normalFont, "Play", PLAY_BUTTON_X, PLAY_BUTTON_Y, '$');
        }

        if(myMouse.checkForClick(window.getFontDimensions(normalFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y))){
            EXIT_BUTTON_Y += buttonOffsetY;
            if(EXIT_BUTTON_Y > 230 || EXIT_BUTTON_Y < 220){
                EXIT_BUTTON_Y -= 2 * buttonOffsetY;
                buttonOffsetY = -1 * buttonOffsetY;
            }
            window.renderFont(normalFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y, 'w');
        }
        else{
            window.renderFont(normalFont, "Exit", EXIT_BUTTON_X, EXIT_BUTTON_Y, '$');
        }

        window.renderFont(titleFont, "Carlos", TITLE_X, TITLE_Y, '$');

        window.renderParticles(numberOfParticles, WINDOW_WIDTH, WINDOW_HEIGHT);

        window.updateRenderer();
    }

    window.cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    std::cout << "Program exited." << std::endl;
}
