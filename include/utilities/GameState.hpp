#pragma once

class HUD;

class GameState {

public:

	static GameState* GetGameState();

	void SetTargetHUD(HUD* hud);

	const int GetScore() const { return m_currentScore; };
	const int GetCurrentLives() const { return m_currentLives; };

	void AddScore(const int increment);
	void PlayerDeath();

	~GameState();

private:
	GameState();

	void GameOver();
	void RestartLevel();

	const int m_maxLives = 3;
	int m_currentLives;
	int m_currentScore = 0;

	HUD* m_hud = nullptr;

	static GameState* s_gameState;
};
