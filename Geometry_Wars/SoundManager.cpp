#include "SoundManager.h"
#include "io/load_file_to_string.h"

#include <SDL.h>
#include <cstdint>
#include <iostream>
#include <bitset>



SDL_AudioSpec SoundManager::output_spec;

SDL_AudioDeviceID SoundManager::audio_device;

std::array<SoundManager::Sound, static_cast<int>(Sounds::NUM_SOUNDS)> SoundManager::sounds;

std::vector<SoundManager::SoundInvocation> SoundManager::sounds_playing;



void print_audio_format_info(const SDL_AudioSpec& spec)
{
    std::bitset<16> bits{ spec.format };
    std::cout << bits.to_string() << "\t" << spec.freq
        << "\t" << static_cast<int>(spec.channels) << "\n";
}


int pos = 0;

void SoundManager::audio_callback(void *udata, uint8_t *stream, int len)
{
    SDL_memset(stream, 0, len);

    auto& s = sounds[0];

    if (pos + len < s.length)
    {
        SDL_memcpy(stream, &s.data[pos], len);
        pos += len;
    }
    else
    {

    }


    //extern SDL_AudioFormat deviceFormat;
    //extern const Uint8 *mixData;
    //SDL_memset(stream, 0, len);  // make sure this is silence.
    // mix our audio against the silence, at 50% volume.
    //SDL_MixAudioFormat(stream, mixData, deviceFormat, len, SDL_MIX_MAXVOLUME / 2);
}




void SoundManager::load_sound(Sounds sound, const std::string& path)
{
    int index = static_cast<int>(sound);

    if (SDL_LoadWAV(path.c_str(), &(sounds[index].spec), &(sounds[index].data), &(sounds[index].length)) == NULL)
    {
        std::cerr << "Error: file could not be loaded as an audio file." << std::endl;
    }
    
    std::cout << "  ";
    print_audio_format_info(sounds[index].spec);

}


void SoundManager::initialize()
{
    auto [path, success] = find_folder("Geometry_Wars");
    auto data_folder = path / "data";

    load_sound(Sounds::THEME, (data_folder / "theme.wav").string());
    load_sound(Sounds::LASER, (data_folder / "laser.wav").string());

    output_spec = sounds[0].spec;
    output_spec.callback = SoundManager::audio_callback;

    audio_device = SDL_OpenAudioDevice(NULL, 0, &output_spec, NULL, 0);

    std::cout << "- ";
    print_audio_format_info(output_spec);
    
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
