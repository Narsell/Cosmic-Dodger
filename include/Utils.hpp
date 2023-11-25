#pragma once

#include <SDL.h>

namespace utils {

	inline float HireTimeInSeconds() 
	{
		float t = (float)SDL_GetTicks64();
		t *= 0.001f;
		return t;
	}

}
