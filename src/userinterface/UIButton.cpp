#include "userinterface/UIButton.hpp"
#include "utilities/ResourceManager.hpp"

UIButton::UIButton(const char* label, const TextureResource* texture, const Transform& transform, const char* name)
	:UITextureRect(texture, transform, name),
	m_normalTexture(texture),
	m_hoverTexture(texture),
	m_label(label, Color::black, Transform(Vector2(15.f, 10.f)), Vector2(170.f, 40.f)),
	m_boundary({ 0.f, 0.f, texture->GetDimensions().x, texture->GetDimensions().y })

{
	AddChild(&m_label);
	SetCanUpdate(true);
}

void UIButton::Construct()
{
	UIElement::Construct();
	m_boundary.x = m_transform.GetPosition().x;
	m_boundary.y = m_transform.GetPosition().y;
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

	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_FRect mouseRect(static_cast<float>(mouseX), static_cast<float>(mouseY), 20.f, 20.f);

	if (SDL_HasIntersectionF(&m_boundary, &mouseRect)) {
		SetTextureResource(m_hoverTexture);
	}
	else {
		SetTextureResource(m_normalTexture);
	}
}

