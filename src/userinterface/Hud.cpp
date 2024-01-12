#include "SDL.h"
#include <sstream>

#include "Window.hpp"
#include "userinterface/Hud.hpp"
#include "components/Transform.hpp"
#include "userinterface/StaticText.hpp"
#include "utilities/Color.hpp"
#include "utilities/GameState.hpp"


HUD::HUD(Window* window)
	:BaseEntity("", "NA_HUD", true, true),
	m_window(window),
	m_lives(new StaticText(this, "LIVES: #", Color::aqua, Transform(Vector2(Window::s_width - 220.f, 20.f)), Vector2(200.f, 50.f))),
	m_score(new StaticText(this, "SCORE: #", Color::aqua, Transform(Vector2(20.f, 20.f)), Vector2(200.f, 50.f))),
	m_ammo(new StaticText(this, "AMMO: #", Color::aqua, Transform(Vector2(20.f, Window::s_height - 70.f)), Vector2(200.f, 50.f)))
{	

	m_textElements.push_back(m_lives);
	m_textElements.push_back(m_score);
	m_textElements.push_back(m_ammo);
}

HUD::~HUD()
{
	for (StaticText* textElement : m_textElements) {
		delete textElement;
	}
}

void HUD::UpdateLives(const int lives)
{
	m_lives->SetText("LIVES: " + std::to_string(lives));
}

void HUD::UpdateScore(const int score)
{
	m_score->SetText("SCORE: " + std::to_string(score));
}

void HUD::UpdateAmmo(const int ammo)
{
	m_ammo->SetText("AMMO: " + std::to_string(ammo));
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
