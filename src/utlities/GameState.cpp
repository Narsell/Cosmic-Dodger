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

void GameState::SetTargetHUD(HUD* hud)
{
	m_hud = hud;
	assert(m_hud);
	m_hud->UpdateScore(m_currentScore);
	m_hud->UpdateHighScore(m_highScore);
	m_hud->UpdateLives(m_currentLives);
}

void GameState::AddScore(const int increment)
{
	m_currentScore += increment;
	m_hud->UpdateScore(m_currentScore);
}


void GameState::PlayerHit()
{
	m_currentLives = std::clamp(m_currentLives - 1, 0, m_maxLives);
	m_playerHit.Play();
	m_hud->UpdateLives(m_currentLives);

	if (m_currentLives == 0) {
		GameOver();
	}

}


void GameState::GameOver()
{
	//It goes like this:
	//				Show dead screen, pause entities updates, wait a for callback and then back to game
	//				Delete all active meteors
	//				Reset shooting component (timers, ammo)
	//				Set current lives back to m_maxLives
	//				Save hi score if score > hi score then set score to 0
	//				Set player position to starting position
	//				Update HUD with new values

	// TODO: Add timer on hud to display GAME OVER message and add za callback to return and update HUD
	
	Player* player = GameManager::GetPlayer();
	ShootingComponent* playerShootComponent = player->GetShootingComponent();
	ResetGameState(*player);

	m_hud->UpdateHighScore(m_highScore);
	m_hud->UpdateScore(m_currentScore);
	m_hud->UpdateLives(m_currentLives);
	m_hud->UpdateAmmo(playerShootComponent->GetCurrentAmmo());

	std::cout << "GAME OVER!\n";
}

void GameState::ResetGameState(Player& player) 
{
	GameManager::GetMeteorSpawner()->Reset();
	GameManager::GetPickupSpawner()->Reset();
	player.GetShootingComponent()->Reset();
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

