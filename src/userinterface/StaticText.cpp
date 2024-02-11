#include "userinterface/StaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "userinterface/Hud.hpp"
#include "Window.hpp"


StaticText::StaticText(HUD* parentHud, const std::string& text, const Color& color, const Transform& transform, const Vector2& dimensions, const char* name)
	:BaseEntity("", name, true, false),
	m_text(text),
	m_color(color),
	m_dimensions(dimensions),
	m_parentHud(parentHud),
	m_transform(transform)
{
	UpdateTexture();
}

StaticText::~StaticText()
{
	SDL_DestroyTexture(m_fontTexture);
}

void StaticText::SetText(const std::string& newText)
{
	m_text = newText;
	UpdateTexture();
}

void StaticText::Render(SDL_Renderer* renderer)
{
	Vector2 position = m_transform.GetPosition();
	SDL_FRect rect(position.x, position.y, m_dimensions.x, m_dimensions.y);

	SDL_RenderCopyF(renderer, m_fontTexture, nullptr, &rect);		
}

void StaticText::UpdateTexture()
{
	SDL_Renderer* renderer = m_parentHud->GetTargetWindow()->GetRenderer();
	assert(renderer);
	m_fontSurface = TTF_RenderText_Solid(ResourceManager::mainFont, m_text.c_str(), m_color.ToSDLColor());
	m_fontTexture = SDL_CreateTextureFromSurface(renderer, m_fontSurface);

	SDL_FreeSurface(m_fontSurface);
}
