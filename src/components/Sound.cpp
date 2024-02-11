#include <assert.h>

#include "components/Sound.hpp"
#include <iostream>

void(*Sound::m_callback)();


Sound::Sound(Mix_Chunk* audio, float volume, const bool looping)
	:m_audio(audio),
	m_channel(-1),
	m_looping(looping),
	m_volume(static_cast<int>(volume * MIX_MAX_VOLUME))
{
	assert(m_audio);
	Mix_ChannelFinished(&Sound::AudioFinished);
}

Sound::~Sound()
{

}

void Sound::Play()
{
	Mix_VolumeChunk(m_audio, m_volume);
	m_channel = Mix_PlayChannel(-1, m_audio, m_looping ? -1 : 0);
}

const bool Sound::IsPlaying() const
{
	if (m_channel < 0) return false;
	return Mix_Playing(m_channel);
}

void Sound::SetVolume(float volume)
{
	Mix_Volume(m_channel, static_cast<int>(volume * MIX_MAX_VOLUME));
}

void Sound::SetOnFinishedCallback(void(*callback)())
{
	m_callback = callback;
}

void Sound::AudioFinished(int m_channel)
{
	if (m_callback) {
		m_callback();
	}
}



