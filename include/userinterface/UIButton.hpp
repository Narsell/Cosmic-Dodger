#pragma once
#include <functional>

#include "userinterface/UITextureRect.hpp"
#include "userinterface/UIStaticText.hpp"
#include "utilities/ResourceManager.hpp"

class UIButton : public UITextureRect {

public:

	UIButton(const char* label, const TextureResource* texture, const Transform& transform, const char* name = "NA_UIButton");
	~UIButton();

	void SetOnPressedDelegate(std::function<void(void)> delegate) { OnPressed = delegate; };
	void SetHoverTexture(const TextureResource* hoverTexture) { m_hoverTexture = hoverTexture; };

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

protected:

	virtual void Construct() override;

private:

	const TextureResource* m_normalTexture;
	const TextureResource* m_hoverTexture;
	UIStaticText m_label;
	SDL_FRect m_boundary;

	std::function<void(void)> OnPressed;
};