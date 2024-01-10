#include "userinterface/StaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"

bool StaticText::s_fontInitialized = false;

StaticText::StaticText(Window* window, const char* text, Transform transform, Vector2 dimensions)
	:m_text(text),
	m_window(window),
	m_transform(transform),
	m_dimensions(dimensions)
{
	ResourceManager::textFont = ResourceManager::LoadFont("assets/kenvector_future_thin.ttf", 50);
}

StaticText::~StaticText()
{
	SDL_DestroyTexture(m_fontTexture);
}

void StaticText::Draw()
{
	SDL_Renderer* renderer = m_window->GetRenderer();

	m_fontSurface = TTF_RenderText_Solid(ResourceManager::textFont, m_text, { 255,255,255 });
	m_fontTexture = SDL_CreateTextureFromSurface(renderer, m_fontSurface);

	SDL_FreeSurface(m_fontSurface);

	Vector2 position = m_transform.GetPosition();
	SDL_FRect rect(position.x, position.y, m_dimensions.x, m_dimensions.y);

	SDL_RenderCopyF(renderer, m_fontTexture, nullptr, &rect);
		
}
