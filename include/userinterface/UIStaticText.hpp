#pragma once

#include "components/Transform.hpp"
#include "userinterface/UIElement.hpp"
#include "utilities/Color.hpp"

struct SDL_Texture;
struct SDL_Surface;
class HUD;

class UIStaticText : public UIElement {

public:

	UIStaticText(const HUD* parentHud, const std::string&, const Color& color, const Transform& transform = Transform(), const Vector2& dimensions = Vector2(10.f, 10.f), const char* name = "NA_StaticText");
	~UIStaticText() override;

	void SetText(const std::string& newText);

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override {};

private:

	void UpdateTexture();

	const char* m_text;
	Color m_color;
	Vector2 m_dimensions;

	SDL_Texture* m_fontTexture = nullptr;
	SDL_Surface* m_fontSurface = nullptr;

};
