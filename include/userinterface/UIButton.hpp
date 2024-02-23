#pragma once

#include "userinterface/UITextureRect.hpp"
#include "userinterface/UIStaticText.hpp"

class UIButton : public UITextureRect {

public:

	UIButton(const char* label, const TextureResource& texture, const Transform& transform, const char* name = "NA_UIButton");
	~UIButton();

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

};