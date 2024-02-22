#include "userinterface/UIStaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "userinterface/Hud.hpp"
#include "Window.hpp"


UIStaticText::UIStaticText(const std::string& text, const Color& color, const Transform& transform, const Vector2& dimensions, const char* name)
	:UIElement(transform, name),
	m_text(text.c_str()),
	m_color(color),
	m_dimensions(dimensions)
{
	UpdateSurfaceWithText();
}

UIStaticText::~UIStaticText()
{
	SDL_FreeSurface(m_fontSurface);
	SDL_DestroyTexture(m_fontTexture);
}

void UIStaticText::SetText(const std::string& newText)
{
	m_text = newText.c_str();
	UpdateSurfaceWithText();
}

void UIStaticText::Render(SDL_Renderer* renderer)
{
	BaseEntity::Render(renderer);

	if (m_updateTexture) {
		UpdateTexture(renderer);
	}

	Vector2 position = m_transform.GetPosition();
	SDL_FRect rect(position.x, position.y, m_dimensions.x, m_dimensions.y);

	SDL_RenderCopyF(renderer, m_fontTexture, nullptr, &rect);		
}

void UIStaticText::UpdateSurfaceWithText()
{
	m_fontSurface = TTF_RenderText_Blended(ResourceManager::mainFont, m_text, m_color.ToSDLColor());
	m_updateTexture = true;
}

void UIStaticText::UpdateTexture(SDL_Renderer* renderer)
{
	m_fontTexture = SDL_CreateTextureFromSurface(renderer, m_fontSurface);
	m_updateTexture = false;
}
