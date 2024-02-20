#pragma once
#include <vector>

#include "userinterface/UIElement.hpp"
#include "userinterface/UITextureRect.hpp"

enum GROW_DIRECTION {
	LEFT,
	RIGHT
};


class UIProgressTextures : public UIElement {

public:
	UIProgressTextures(const HUD* parentHud, const Transform& transform, TextureResource* texture, const int maxValue, const char* name = "NA_UIProgressTextures");
	~UIProgressTextures() override;

	void UpdateValue(const int currentValue);

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override {};

private:

	const int m_maxValue;
	int m_currentValue;
	const float m_padding = 5;
	GROW_DIRECTION m_growDirection = GROW_DIRECTION::LEFT;

	TextureResource* m_textureResource = nullptr;
	std::vector<UITextureRect*> m_textures;

};
