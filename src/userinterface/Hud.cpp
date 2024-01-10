#include "SDL.h"

#include "Hud.hpp"
#include "Window.hpp"
#include "components/Transform.hpp"
#include "userinterface/StaticText.hpp"

HUD::HUD(Window* window)
	:BaseEntity("", "NA_HUD", true, true),
	m_window(window)
{
	m_lives = new StaticText(m_window, "LIVES: 3", Transform(Vector2(1080.f, 20.f)), Vector2(200.f, 50.f));
	m_score = new StaticText(m_window, "SCORE: 0", Transform(Vector2(20.f, 20.f)), Vector2(200.f, 50.f));

	m_textElements.push_back(m_lives);
	m_textElements.push_back(m_score);
}

HUD::~HUD()
{
	for (StaticText* textElement : m_textElements) {
		delete textElement;
	}
}

void HUD::Render(SDL_Renderer* renderer)
{
	for (StaticText* textElement : m_textElements) {
		if (textElement->GetCanRender()) {
			textElement->Render(renderer);
		}
	}
}

void HUD::Update(const float deltaTime)
{
}
