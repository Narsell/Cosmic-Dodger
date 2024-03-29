#pragma once
#include <sstream>

#include "components/Transform.hpp"
#include "userinterface/UIElement.hpp"
#include "utilities/Color.hpp"

struct TextureResource;
class HUD;

class UITextureRect : public UIElement {

public:

	UITextureRect(const TextureResource* texture, const Transform& transform = Transform(), const char* name = "NA_TextureRect");
	~UITextureRect() override;

	void SetTextureResource(const TextureResource* texture) { m_textureResource = texture; };

	virtual void Render(SDL_Renderer* renderer) override;

private:

	const TextureResource* m_textureResource;
};
