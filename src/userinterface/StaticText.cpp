#include "userinterface/StaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"

bool StaticText::s_fontInitialized = false;

StaticText::StaticText(Window* window, const char* text, const Color& color, Transform transform, Vector2 dimensions, const char* name)
	:BaseEntity("", name, true, false),
	m_text(text),
	m_color(color),
	m_window(window),
	m_transform(transform),
	m_dimensions(dimensions)
{
	ResourceManager::textFont = ResourceManager::LoadFont("assets/kenvector_future_thin.ttf", 50);

	m_fontSurface = TTF_RenderText_Solid(ResourceManager::textFont, m_text, m_color.ToSDLColor());
	m_fontTexture = SDL_CreateTextureFromSurface(m_window->GetRenderer(), m_fontSurface);

	SDL_FreeSurface(m_fontSurface);
}

StaticText::~StaticText()
{
	SDL_DestroyTexture(m_fontTexture);
}

void StaticText::SetText(const char* newText)
{
	m_text = newText;
	m_fontSurface = TTF_RenderText_Solid(ResourceManager::textFont, m_text, m_color.ToSDLColor());
	m_fontTexture = SDL_CreateTextureFromSurface(m_window->GetRenderer(), m_fontSurface);

	SDL_FreeSurface(m_fontSurface);
}

void StaticText::Render(SDL_Renderer* renderer)
{
	Vector2 position = m_transform.GetPosition();
	SDL_FRect rect(position.x, position.y, m_dimensions.x, m_dimensions.y);

	SDL_RenderCopyF(renderer, m_fontTexture, nullptr, &rect);		
}
