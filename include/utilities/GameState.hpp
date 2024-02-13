#pragma once
#include "utilities/Math.hpp"
#include "components/Sound.hpp"

class HUD;
class Player;

class GameState {

public:

	static GameState* GetGameState();

	void SetTargetHUD(HUD* hud);

	const int GetScore() const { return m_currentScore; };
	const int GetCurrentLives() const { return m_currentLives; };
	const int GetMaxLives() const { return m_maxLives; };
	const Vector2& GetPlayerStartPosition() const { return m_startPosition; };

	void AddScore(const int increment);
	void PlayerHit();

	~GameState();

private:
	GameState();

	void GameOver();
	void ResetGameState(Player& player);

	Vector2 m_startPosition;
	const int m_maxLives = 3;
	int m_currentLives;
	int m_currentScore = 0;
	int m_highScore = 0;

	HUD* m_hud = nullptr;

	Sound m_playerHit;

	static GameState* s_gameState;
};
