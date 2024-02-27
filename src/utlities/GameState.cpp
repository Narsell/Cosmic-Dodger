#include <algorithm>
#include <assert.h>

#include "entities/Player.hpp"
#include "utilities/MeteorSpawner.hpp"
#include "utilities/PickupSpawner.hpp"
#include "utilities/GameState.hpp"
#include "utilities/ResourceManager.hpp"
#include "userinterface/Hud.hpp"
#include "components/ShootingComponent.hpp"
#include "Window.hpp"
#include "GameManager.hpp"

GameState* GameState::s_gameState = nullptr;

GameState::GameState()
	:m_startPosition(
		Window::s_width / 2.f - ResourceManager::playerTexture->GetDimensions().x / 2.f,
		Window::s_height / 2.f - ResourceManager::playerTexture->GetDimensions().y / 2.f
	),
	m_currentLives(m_maxLives),
	m_playerHit(ResourceManager::explosionSound, 0.5f)
{
}

GameState* GameState::GetGameState()
{
	if (!s_gameState) {
		s_gameState = new GameState();
	}
	return s_gameState;
}

void GameState::OnTryAgain()
{
	SetIsPaused(false);
	m_hud->SetState(HUD_STATE::PLAYING);
}

void GameState::SetTargetHUD(HUD* hud)
{
	m_hud = hud;
	assert(m_hud);
	m_hud->UpdateScore(m_currentScore);
	m_hud->UpdateHighScore(m_highScore);
	m_hud->UpdateLives(m_currentLives);
	m_hud->UpdateDifficultyLevel(m_difficultyLevel);
}

void GameState::AddScore(const int increment)
{
	m_currentScore += increment;
	m_hud->UpdateScore(m_currentScore);
	if (m_currentScore % m_scoreAmountToIncreseDiff == 0) {
		IncreaseDifficulty();
	}
}


void GameState::OnPlayerHit()
{
	m_currentLives = std::clamp(m_currentLives - 1, 0, m_maxLives);
	m_playerHit.Play();
	m_hud->UpdateLives(m_currentLives);

	if (m_currentLives == 0) {
		GameOver();
	}

}


void GameState::IncreaseDifficulty()
{
	++m_difficultyLevel;
	GameManager::GetMeteorSpawner()->IncreaseDifficulty();
	m_hud->UpdateDifficultyLevel(m_difficultyLevel);
}

void GameState::GameOver()
{
	SetIsPaused(true);
	m_hud->UpdateDeathMenu(m_currentScore, m_difficultyLevel);
	m_hud->SetState(HUD_STATE::DEAD);

	Player* player = GameManager::GetPlayer();
	ResetGameState(*player);
	UpdateHUD(*player);

}

void GameState::UpdateHUD(const Player& player)
{
	ShootingComponent* playerShootComponent = player.GetShootingComponent();

	m_hud->UpdateHighScore(m_highScore);
	m_hud->UpdateScore(m_currentScore);
	m_hud->UpdateLives(m_currentLives);
	m_hud->UpdateAmmo(playerShootComponent->GetCurrentAmmo());
	m_hud->UpdateDifficultyLevel(m_difficultyLevel);
}

void GameState::ResetGameState(Player& player) 
{
	GameManager::GetMeteorSpawner()->Reset();
	GameManager::GetPickupSpawner()->Reset();
	player.GetShootingComponent()->Reset();
	m_difficultyLevel = 1;
	m_currentLives = m_maxLives;
	if (m_currentScore > m_highScore) {
		m_highScore = m_currentScore;
	}
	m_currentScore = 0;
	player.m_transform.SetPosition(m_startPosition);

}


GameState::~GameState()
{
}

