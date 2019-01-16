#pragma once

#include <vector>
#include <mutex>
#include <array>

#include <SDL.h>




/// enum class Sounds
/**
 *  This enum has one value for every sound that can be played in the game.
 *  Allows the user to play sounds with the SoundManager without having to know how
 *  SounManager internally stores its sounds.
 */
enum class Sounds : int
{
    THEME = 0,
    LASER = 1,
    EXPLOSION = 2,
    // ADD MORE SOUNDS HERE

    NUM_SOUNDS // This has to be the last value in the enum!
};



/// class SoundManager
/**
 *  The SoundManager class is used to play sounds over the speakers.
 *  it only has static methods/ members, which makes it behave more like
 *  a namespace which also has a private part.
 */
class SoundManager
{

public:


    /// Initializes the SDL audio strea, and loads all the sounds in the data folder.
    static void initialize();


    /// deallocates the resources held by SoundManager and closes the audiostream.
    static void shutdown();


    /// Plays the sound that belongs the the SOunds enum value.
    static void play(Sounds sound, bool loop = false);


    /// Stop all currently playing sounds.
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

