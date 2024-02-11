#pragma once
#include "SDL.h"
#include <sstream>
#include <SDL_Mixer.h>

enum AUDIO_CHANNEL {
	MASTER = 1,
	MUSIC,
	SFX,
};

class Sound {

public:

	Sound(Mix_Chunk* audio, AUDIO_CHANNEL channel = AUDIO_CHANNEL::MASTER, float volume = 1.0, const bool looping = false);
	~Sound();

	virtual void Play();

	static void SetChannelVolume(AUDIO_CHANNEL channel, float volume);

private:
	
	Mix_Chunk* m_audio;
	AUDIO_CHANNEL m_channel;
	const bool m_looping;
	int m_volume;

};