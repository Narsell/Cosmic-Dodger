#include "SDL.h"
#include <sstream>

#include "userinterface/Hud.hpp"
#include "Window.hpp"
#include "components/Transform.hpp"
#include "components/ShootingComponent.hpp"
#include "utilities/Color.hpp"
#include "utilities/GameState.hpp"
#include "utilities/ResourceManager.hpp"




HUD::HUD()
	:UIElement(Transform()),
	m_livesProgress(
		Transform(Vector2(Window::s_width - ResourceManager::playerLifeTexture->GetDimensions().x - 30.f, 30.f)), *ResourceManager::playerLifeTexture, GameState::GetGameState()->GetMaxLives()
	),
	m_ammoProgress(
		Transform(Vector2(Window::s_width - ResourceManager::ammoTexture->GetDimensions().x - 30.f, 90.f)), *ResourceManager::ammoTexture, ShootingComponent::GetMaxAmmo()
	),
	m_score(
		"SCORE: #", Color(176, 228, 16), Transform(Vector2(20.f, 20.f)), Vector2(200.f, 50.f)
	),
	m_highScore(
		"HI SCORE: #", Color(255, 0, 160), Transform(Vector2(20.f, 80)), Vector2(100.f, 25.f)
	),
	m_difficultyLevel(
		"LEVEL: #", Color(176, 228, 16), Transform(Vector2(20.f, Window::s_height - 70.f)), Vector2(160.f, 40.f)
	),
	m_deathMenu(
		Transform(Vector2(Window::s_width/2.f, Window::s_height/2.f))
	)


{	
	AddChild(&m_livesProgress);
	AddChild(&m_ammoProgress);
	AddChild(&m_score);
	AddChild(&m_highScore);
	AddChild(&m_difficultyLevel);
	AddChild(&m_deathMenu);
	
	SetCanUpdate(true);

	SetState(HUD_STATE::PLAYING);
}

HUD::~HUD()
{
}

void HUD::SetState(HUD_STATE state)
{
	switch (state)
	{
	case PLAYING:
		m_deathMenu.SetCanRender(false);
		m_livesProgress.SetCanRender(true);
		m_ammoProgress.SetCanRender(true);
		m_score.SetCanRender(true);
		m_highScore.SetCanRender(true);
		m_difficultyLevel.SetCanRender(true);
		break;
	case DEAD:
		m_deathMenu.SetCanRender(true);
		m_livesProgress.SetCanRender(false);
		m_ammoProgress.SetCanRender(false);
		m_score.SetCanRender(false);
		m_highScore.SetCanRender(false);
		m_difficultyLevel.SetCanRender(false);
		break;
	default:
		break;
	}
}

void HUD::UpdateDeathMenu(const int currentScore, const int difficulty)
{
	m_deathMenu.UpdateValues(currentScore, difficulty);
}

void HUD::UpdateLives(const int lives)
{
	m_livesProgress.UpdateValue(lives);
}

void HUD::UpdateScore(const int score)
{
	m_score.SetText("SCORE: " + std::to_string(score));
}

void HUD::UpdateHighScore(const int highScore)
{
	m_highScore.SetText("HI SCORE: " + std::to_string(highScore));
}

void HUD::UpdateAmmo(const int ammo)
{
	m_ammoProgress.UpdateValue(ammo);
}

void HUD::UpdateDifficultyLevel(const int difficultyLevel)
{

	m_difficultyLevel.SetText("LEVEL: " + std::to_string(difficultyLevel));
}


void HUD::Render(SDL_Renderer* renderer)
{
	UIElement::Render(renderer);
}

void HUD::Update(const float deltaTime)
{
	UIElement::Update(deltaTime);
}
