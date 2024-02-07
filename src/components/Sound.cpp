#include "components/Sound.hpp"
#include <iostream>

Sound::Sound(const std::string& filepath, AUDIO_CHANNEL channel, float volume, const bool looping)
	:m_audio(nullptr),
	m_channel(channel),
	m_looping(looping),
	m_volume(static_cast<int>(volume * MIX_MAX_VOLUME))
{
	//Load this from resource manager
	m_audio = Mix_LoadWAV(filepath.c_str());
}

Sound::~Sound()
{
	Mix_FreeChunk(m_audio);

}

void Sound::Play()
{
	Mix_VolumeChunk(m_audio, m_volume);
	Mix_PlayChannel(m_channel, m_audio, m_looping ? -1 : 0);
}




