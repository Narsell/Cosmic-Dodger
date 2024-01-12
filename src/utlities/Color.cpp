#include "utilities/Color.hpp"

Color Color::red = Color(255, 0, 0);
Color Color::green = Color(0, 255, 0);
Color Color::blue = Color(0, 0, 255);
Color Color::aqua = Color(0, 255, 255);

Color::Color(const int r, const int g, const int b, const int a)
	:m_r(r), m_g(g), m_b(b), m_a(a)
{
}

SDL_Color Color::ToSDLColor()
{
	return SDL_Color(m_r, m_g, m_b);
}
