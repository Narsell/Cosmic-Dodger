#include "SDL.h"
#include <sstream>

#include "Window.hpp"
#include "userinterface/Hud.hpp"
#include "components/Transform.hpp"
#include "userinterface/StaticText.hpp"
#include "userinterface/UIProgressTextures.hpp"
#include "utilities/Color.hpp"
#include "utilities/GameState.hpp"
#include "utilities/ResourceManager.hpp"


HUD::HUD(Window* window)
	:BaseEntity("", "NA_HUD", true, true),
	m_window(window),
	m_livesProgress(
		new UIProgressTextures(this, Transform(Vector2(Window::s_width - 30.f - ResourceManager::playerLifeTexture->GetDimensions().x, 30.f)), ResourceManager::playerLifeTexture, GameState::GetGameState()->GetMaxLives())
	),
	m_ammoProgress(
		new UIProgressTextures(this, Transform(Vector2(Window::s_width - 30.f - ResourceManager::ammoTexture->GetDimensions().x, 90.f)), ResourceManager::ammoTexture, 15)
	),
	m_score(
		new UIStaticText(this, "SCORE: #", Color(176, 228, 16), Transform(Vector2(20.f, 20.f)), Vector2(200.f, 50.f))
	),
	m_highScore(
		new UIStaticText(this, "HI SCORE: #", Color(255, 0, 160), Transform(Vector2(20.f, 80)), Vector2(100.f, 25.f))
	),
	m_difficultyLevel(
		new UIStaticText(this, "LEVEL: #", Color(176, 228, 16), Transform(Vector2(20.f, Window::s_height - 70.f)), Vector2(160.f, 40.f))
	)
	
{	
	m_uiElements.push_back(m_livesProgress);
	m_uiElements.push_back(m_ammoProgress);
	m_uiElements.push_back(m_score);
	m_uiElements.push_back(m_highScore);
	m_uiElements.push_back(m_difficultyLevel);
}

HUD::~HUD()
{
	for (UIElement* uiElement : m_uiElements) {
		delete uiElement;
	}
}

void HUD::UpdateLives(const int lives)
{
	m_livesProgress->UpdateValue(lives);
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
	m_ammoProgress->UpdateValue(ammo);
}

void HUD::UpdateDifficultyLevel(const int difficultyLevel)
{
	m_difficultyLevel->SetText("LEVEL: " + std::to_string(difficultyLevel));
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
