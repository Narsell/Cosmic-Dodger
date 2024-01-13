#include <algorithm>
#include <assert.h>

#include "utilities/GameState.hpp"
#include "userinterface/Hud.hpp"

GameState* GameState::s_gameState = nullptr;

GameState::GameState()
	:m_currentLives(m_maxLives)
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
	m_hud->UpdateLives(m_currentLives);
}

void GameState::AddScore(const int increment)
{
	m_currentScore += increment;
	if(m_hud)
		m_hud->UpdateScore(m_currentScore);
}


void GameState::PlayerDeath()
{
	m_currentLives = std::clamp(m_currentLives - 1, 0, 1);

	if(m_hud)
		m_hud->UpdateLives(m_currentLives);

	if (m_currentLives == 0) {
		GameOver();
	}
	else {
		RestartLevel();
	}
}

void GameState::RestartLevel()
{
	//TODO: Restart current level by resetting player position 
	//		Set player ammo back to full
	//		Set player health back to full
	//		Delete all active meteors
	m_currentScore = 0;
}

void GameState::GameOver()
{
	//TODO: Restart everything: Restart level
	//							Set current lives back to m_maxLives
	//							Show dead screen, wait a bit and then back to game
	std::cout << "Game over!\n";
}


GameState::~GameState()
{
}

