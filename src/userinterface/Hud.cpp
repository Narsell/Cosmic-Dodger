#include "SDL.h"
#include <sstream>

#include "Window.hpp"
#include "userinterface/Hud.hpp"
#include "components/Transform.hpp"
#include "userinterface/StaticText.hpp"
#include "userinterface/PlayerLives.hpp"
#include "utilities/Color.hpp"
#include "utilities/GameState.hpp"
#include "utilities/ResourceManager.hpp"


HUD::HUD(Window* window)
	:BaseEntity("", "NA_HUD", true, true),
	m_window(window),
	m_lives(
		new UIPlayerLives(this, Transform(Vector2(Window::s_width - 161.f, 20.f)), GameState::GetGameState()->GetMaxLives())
	),
	m_score(
		new UIStaticText(this, "SCORE: #", Color::aqua, Transform(Vector2(20.f, 20.f)), Vector2(200.f, 50.f))
	),
	m_highScore(
		new UIStaticText(this, "HI SCORE: #", Color::aqua, Transform(Vector2(20.f, 80)), Vector2(120.f, 30.f))
	),
	m_ammo(
		new UIStaticText(this, "AMMO: #", Color::aqua, Transform(Vector2(20.f, Window::s_height - 70.f)), Vector2(200.f, 50.f))
	)
	
{	
	m_uiElements.push_back(m_lives);
	m_uiElements.push_back(m_score);
	m_uiElements.push_back(m_highScore);
	m_uiElements.push_back(m_ammo);
}

HUD::~HUD()
{
	for (UIElement* uiElement : m_uiElements) {
		delete uiElement;
	}
}

void HUD::UpdateLives(const int lives)
{
	m_lives->UpdateCurrentLives(lives);
}

void HUD::UpdateScore(const int score)
{
	m_score->SetText("SCORE: " + std::to_string(score));
}

void HUD::UpdateHighScore(const int highScore)
{
	m_highScore->SetText("HI SCORE: " + std::to_string(highScore));
}

void HUD::UpdateAmmo(const int ammo)
{
	m_ammo->SetText("AMMO: " + std::to_string(ammo));
}


void HUD::Render(SDL_Renderer* renderer)
{
	for (UIElement* uiElement : m_uiElements) {
		if (uiElement->GetCanRender()) {
			uiElement->Render(renderer);
		}
	}
}

void HUD::Update(const float deltaTime)
{
}
