#include "SoundManager.h"
#include "io/load_file_to_string.h"

#include <SDL.h>
#include <cstdint>
#include <iostream>
#include <bitset>



SDL_AudioDeviceID SoundManager::audio_device;

std::array<SoundManager::Sound, static_cast<int>(Sounds::NUM_SOUNDS)> SoundManager::sounds;



void print_audio_format_bits(SDL_AudioFormat f)
{
    std::bitset<16> bits{ f };
    std::cout << bits.to_string() << std::endl;
}




void SoundManager::load_sound(Sounds sound, const std::string& path)
{
    int index = static_cast<int>(sound);

    if (SDL_LoadWAV(path.c_str(), &(sounds[index].spec), &(sounds[index].data), &(sounds[index].length)) == NULL)
    {
        std::cerr << "Error: file could not be loaded as an audio file." << std::endl;
    }
}


void SoundManager::initialize()
{
    auto [path, success] = find_folder("Geometry_Wars");
    auto data_folder = path / "data";

    load_sound(Sounds::THEME, (data_folder / "theme.wav").string());
    load_sound(Sounds::LASER, (data_folder / "laser.wav").string());

    audio_device = SDL_OpenAudioDevice(NULL, 0, &(sounds[0].spec), NULL, 0);

    SDL_PauseAudioDevice(audio_device, 0);
}


void SoundManager::shutdown()
{
    for (int i = 0; i < static_cast<int>(Sounds::NUM_SOUNDS); ++i)
    {
        SDL_FreeWAV(sounds[i].data);
    }

    SDL_CloseAudioDevice(audio_device);
}


void SoundManager::play(Sounds sound)
{
    stop();
    int index = static_cast<int>(sound);
    SDL_QueueAudio(audio_device, sounds[index].data, sounds[index].length);
}


void SoundManager::stop()
{
    SDL_ClearQueuedAudio(audio_device);
}
