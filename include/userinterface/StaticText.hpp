#pragma once
#include "components/Transform.hpp"
#include "entities/BaseEntity.hpp"
#include "utilities/Color.hpp"

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;
class Window;

class StaticText : public BaseEntity {

public:

	StaticText(Window* window, const char* text, const Color& color, Transform transform = Transform(), Vector2 dimensions = Vector2(10.f, 10.f), const char* name = "NA_StaticText");
	~StaticText();

	void SetText(const char* newText);

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override {};

	Transform m_transform;
private:

	const char* m_text;
	Color m_color;
	Vector2 m_dimensions;

	Window* m_window = nullptr;
	static bool s_fontInitialized;
	SDL_Texture* m_fontTexture = nullptr;
	SDL_Surface* m_fontSurface = nullptr;

};
