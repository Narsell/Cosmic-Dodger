#include "userinterface/UIButton.hpp"

UIButton::UIButton(const char* label, const TextureResource& texture, const Transform& transform, const char* name)
	:UITextureRect(texture, transform, name)
{
}

UIButton::~UIButton()
{
}

void UIButton::Render(SDL_Renderer* renderer)
{
	UITextureRect::Render(renderer);
}

void UIButton::Update(const float deltaTime)
{
	UIElement::Update(deltaTime);
}
