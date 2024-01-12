#pragma once
#include <sstream>

#include "components/Transform.hpp"
#include "entities/BaseEntity.hpp"
#include "utilities/Color.hpp"

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;
class HUD;

class StaticText : public BaseEntity {

public:

	StaticText(HUD* parentHud, const std::string& text, const Color& color, const Transform& transform = Transform(), const Vector2& dimensions = Vector2(10.f, 10.f), const char* name = "NA_StaticText");
	~StaticText();

	void SetText(const std::string& newText);

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override {};

	Transform m_transform;
private:

	void UpdateTexture();

	std::string m_text;
	Color m_color;
	Vector2 m_dimensions;

	SDL_Texture* m_fontTexture = nullptr;
	SDL_Surface* m_fontSurface = nullptr;

	HUD* m_parentHud;
};
