#pragma once

#include <SDL.h>

namespace utils {

	inline float HireTimeInSeconds() 
	{
		float t = SDL_GetTicks64();
		t *= 0.001f;
		return t;
	}

}
