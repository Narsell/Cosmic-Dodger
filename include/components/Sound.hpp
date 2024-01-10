#pragma once
#include "SDL.h"
#include <sstream>

class ISound {

public:
	virtual ~ISound() {};

	virtual void PlaySound() = 0;
	virtual void StopSound() = 0;
};

class Sound : public ISound {

public:

	Sound(std::string filepath);
	~Sound();

	virtual void PlaySound() override;
	virtual void StopSound() override;


private:
	
	void SetupDevice();

	//Device the sound will play on
	SDL_AudioDeviceID m_device;

	//Properties of the wave file that is loaded
	SDL_AudioSpec m_audioSpec;
	Uint8* m_waveStart;
	Uint32 m_waveLenght;

};