#pragma once

#include <array>
#include <SDL.h>


enum class Sounds : int
{
    THEME = 0,
    LASER = 1,
    // ADD MORE SOUNDS HERE

    NUM_SOUNDS // This has to be the last value in the enum!
};



class SoundManager
{

public:


    static void initialize();

    static void shutdown();


    static void play(Sounds sound);

    static void stop();


private:

    static void load_sound(Sounds sound, const std::string& path);


    struct Sound
    {
        SDL_AudioSpec spec;
        uint8_t * data;
        uint32_t length;
    };


    static SDL_AudioDeviceID audio_device;

    static std::array<Sound, static_cast<int>(Sounds::NUM_SOUNDS)> sounds;


};

