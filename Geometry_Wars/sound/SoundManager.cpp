#include "sound/SoundManager.h"

#include "utility/io.h"

#include <SDL.h>
#include <cstdint>
#include <iostream>
#include <bitset>



SDL_AudioSpec SoundManager::output_spec;

SDL_AudioDeviceID SoundManager::audio_device;

std::mutex SoundManager::audio_mutex;


std::array<SoundManager::Sound, static_cast<int>(Sounds::NUM_SOUNDS)> SoundManager::sounds;

std::vector<SoundManager::SoundInvocation> SoundManager::sounds_playing;




void print_audio_format_info(const SDL_AudioSpec& spec)
{
    std::bitset<16> bits{ spec.format };
    std::cout << bits.to_string() << "\t" << spec.freq
        << "\t" << static_cast<int>(spec.channels) << "\n";
}




void SoundManager::audio_callback(void *unused, uint8_t *stream, int num_bytes_desired)
{
    SDL_memset(stream, 0, num_bytes_desired);

    std::lock_guard lock{ audio_mutex };

    for (auto& sound : sounds_playing)
    {
        auto sound_data = sound.sound->data;
        auto sound_length = sound.sound->num_bytes;

        if (sound.position + num_bytes_desired < sound_length)
        {
            SDL_MixAudioFormat(stream, sound_data + sound.position, output_spec.format, num_bytes_desired, sound.sound->volume);
            sound.position += num_bytes_desired;
        }
        else
        {
            if (sound.loop)
            {
                auto first_half = sound_length - sound.position;
                auto second_half = (sound.position + num_bytes_desired) - sound_length;
                SDL_MixAudioFormat(stream, sound_data + sound.position, output_spec.format, first_half, sound.sound->volume);
                SDL_MixAudioFormat(stream, sound_data + first_half, output_spec.format, second_half, sound.sound->volume);
                sound.position = second_half;
            }
            else
            {
                auto remainder = sound_length - sound.position;
                SDL_MixAudioFormat(stream, sound_data + sound.position, output_spec.format, remainder, sound.sound->volume);
                sound.finished = true;
            }
        }
    }

    sounds_playing.erase(
        std::remove_if(
            sounds_playing.begin(), 
            sounds_playing.end(),
            [](auto& s) { return s.finished; }
        ), 
        sounds_playing.end()
    );
}



void SoundManager::load_sound(Sounds sound, const std::string& path, int volume)
{
    int index = static_cast<int>(sound);

    if (SDL_LoadWAV(path.c_str(), &(sounds[index].spec), &(sounds[index].data), &(sounds[index].num_bytes)) == NULL)
    {
        std::cerr << "Error: file could not be loaded as an audio file." << std::endl;
    }
    sounds[index].volume = volume;
    
    std::cout << "  ";
    print_audio_format_info(sounds[index].spec);
}



void SoundManager::initialize()
{
    auto [path, success] = find_folder("Geometry_Wars");
    auto data_folder = path / "data";

    load_sound(Sounds::THEME, (data_folder / "theme.wav").string(), 128);
    load_sound(Sounds::LASER, (data_folder / "laser.wav").string(), 40);
    load_sound(Sounds::EXPLOSION, (data_folder / "explosion.wav").string(), 128);

    output_spec = sounds[0].spec;
    output_spec.callback = SoundManager::audio_callback;

    audio_device = SDL_OpenAudioDevice(NULL, 0, &output_spec, NULL, 0);

    std::cout << "- ";
    print_audio_format_info(output_spec);
    
    SDL_PauseAudioDevice(audio_device, 0);
}


void SoundManager::shutdown()
{
    std::lock_guard lock{ audio_mutex };

    sounds_playing.clear();

    for (int i = 0; i < static_cast<int>(Sounds::NUM_SOUNDS); ++i)
    {
        SDL_FreeWAV(sounds[i].data);
    }

    SDL_CloseAudioDevice(audio_device);
}


void SoundManager::play(Sounds sound, bool loop)
{
    std::lock_guard lock{ audio_mutex };

    sounds_playing.emplace_back();
    sounds_playing.back().sound = &sounds[static_cast<int>(sound)];
    sounds_playing.back().loop = loop;


}


void SoundManager::stop()
{
    SDL_ClearQueuedAudio(audio_device);
}
