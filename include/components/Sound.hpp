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

	Sound(Mix_Chunk* audio, float volume = 1.0, const bool looping = false);
	~Sound();

	virtual void Play();

	const bool IsPlaying() const;
	void SetVolume(float volume);
	void SetOnFinishedCallback(void(*callback)());

private:
	static void AudioFinished(int m_channel);
	static void(*m_callback)();
	
	Mix_Chunk* m_audio;
	int m_channel;
	const bool m_looping;
	int m_volume;

};