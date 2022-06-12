/*
Libraries in header file:
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
*/

#include "Sound.hpp"

Sound::Sound()
{

}

void Sound::openAudioChannels()
{
    Mix_OpenAudio(frequency, format, channels, chunkSize);
}

void Sound::playMusic(const char* pSoundFileName)
{
    sound = Mix_LoadWAV(pSoundFileName);
    if(sound == nullptr){
        std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
    }

    Mix_PlayChannel(-1,sound, 0);
}


