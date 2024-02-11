#include <assert.h>

#include "components/Sound.hpp"
#include <iostream>

Sound::Sound(Mix_Chunk* audio, AUDIO_CHANNEL channel, float volume, const bool looping)
	:m_audio(audio),
	m_channel(channel),
	m_looping(looping),
	m_volume(static_cast<int>(volume * MIX_MAX_VOLUME))
{
	assert(m_audio);
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

void Sound::SetChannelVolume(AUDIO_CHANNEL channel, float volume)
{
	Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
}




