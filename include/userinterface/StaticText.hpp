#pragma once
#include "Transform.hpp"

struct SDL_Texture;
struct SDL_Surface;
class Window;

class StaticText {

public:

	StaticText(Window* window, const char* text, Transform transform = Transform(), Vector2 dimensions = Vector2(10.f, 10.f));
	~StaticText();

	void Draw();

	Transform m_transform;
private:

	const char* m_text;
	Vector2 m_dimensions;

	Window* m_window = nullptr;
	static bool s_fontInitialized;
	SDL_Texture* m_fontTexture = nullptr;
	SDL_Surface* m_fontSurface = nullptr;

};
