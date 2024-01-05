#include "Sound.hpp"
#include <iostream>

Sound::Sound(std::string filepath)
{
	if (SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLenght) == nullptr) {
		std::cerr << "Error loading sound: " << SDL_GetError() << "\n";
	}
	SetupDevice();
}

Sound::~Sound()
{
	SDL_FreeWAV(m_waveStart);
	SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound()
{
	int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLenght);
	if (status < 0) {
		std::cerr << "Failed to queue sound: " << SDL_GetError() << "\n";
	}
	SDL_PauseAudioDevice(m_device, 0);
}

void Sound::StopSound()
{
	SDL_PauseAudioDevice(m_device, 1);
}

void Sound::SetupDevice()
{
	m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, 0);
	if (!m_device) {
		std::cerr << "Sound device error: " << SDL_GetError() << "\n";
	}
}


