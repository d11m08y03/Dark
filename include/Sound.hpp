#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound{
private:
    int frequency = 22050;
    Uint16 format = AUDIO_S16SYS;
    int channels = 2;
    int chunkSize = 4096;
    Mix_Chunk* sound;

public:
    // Constructor
    Sound();

    // Methods
    void openAudioChannels();
    void playMusic(const char* pSoundFileName);
};