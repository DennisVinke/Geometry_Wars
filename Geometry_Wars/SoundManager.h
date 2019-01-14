#pragma once

#include <vector>
#include <mutex>
#include <array>
#include <SDL.h>


enum class Sounds : int
{
    THEME = 0,
    LASER = 1,
    EXPLOSION = 2,
    // ADD MORE SOUNDS HERE

    NUM_SOUNDS // This has to be the last value in the enum!
};



class SoundManager
{

public:


    static void initialize();

    static void shutdown();


    static void play(Sounds sound, bool loop = false);

    static void stop();


private:

    static void load_sound(Sounds sound, const std::string& path, int volume);

    
    static void audio_callback(void * udata, uint8_t * stream, int len);


    struct Sound
    {
        SDL_AudioSpec spec;
        uint8_t * data;
        uint32_t num_bytes;
        int volume;
    };

    struct SoundInvocation
    {
        Sound* sound = nullptr;
        uint32_t position = 0;
        bool loop = false;
        bool finished = false;
    };


    static SDL_AudioSpec output_spec;

    static std::mutex audio_mutex;

    static SDL_AudioDeviceID audio_device;

    static std::vector<SoundInvocation> sounds_playing;

    static std::array<Sound, static_cast<int>(Sounds::NUM_SOUNDS)> sounds;


};

