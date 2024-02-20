#include "userinterface/UIStaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "userinterface/Hud.hpp"
#include "Window.hpp"


UIStaticText::UIStaticText(const HUD* parentHud, const std::string& text, const Color& color, const Transform& transform, const Vector2& dimensions, const char* name)
	:UIElement(parentHud, transform, name),
	m_text(text.c_str()),
	m_color(color),
	m_dimensions(dimensions)
{
	UpdateTexture();
}

UIStaticText::~UIStaticText()
{
	SDL_DestroyTexture(m_fontTexture);
}

void UIStaticText::SetText(const std::string& newText)
{
	m_text = newText.c_str();
	UpdateTexture();
}

void UIStaticText::Render(SDL_Renderer* renderer)
{
	Vector2 position = m_transform.GetPosition();
	SDL_FRect rect(position.x, position.y, m_dimensions.x, m_dimensions.y);

	SDL_RenderCopyF(renderer, m_fontTexture, nullptr, &rect);		
}

void UIStaticText::UpdateTexture()
{
	SDL_Renderer* renderer = GetParentHud()->GetTargetWindow()->GetRenderer();
	assert(renderer);
	m_fontSurface = TTF_RenderText_Blended(ResourceManager::mainFont, m_text, m_color.ToSDLColor());
	m_fontTexture = SDL_CreateTextureFromSurface(renderer, m_fontSurface);

	SDL_FreeSurface(m_fontSurface);
}
