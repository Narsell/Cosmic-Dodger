#pragma once
#include "SDL.h"

class Color {
public:

	Color(const int r, const int g, const int b, const int a = 1.f);
	~Color() {};

	SDL_Color ToSDLColor();

	static Color red;
	static Color blue;
	static Color green;
	static Color aqua;

private:

	int m_r;
	int m_g;
	int m_b;
	int m_a;
};
