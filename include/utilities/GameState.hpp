#pragma once
#include "utilities/Math.hpp"
#include "components/Sound.hpp"

class HUD;
class Player;

class GameState {

public:

	static GameState* GetGameState();
	GameState(const GameState&) = delete;
	const GameState& operator=(const GameState&) = delete;

	void OnTryAgain();
	void OnPlayerHit();
	void AddScore(const int increment);
	void SetIsPaused(const bool isPaused) { m_isPaused = isPaused; };
	void SetTargetHUD(HUD* hud);

	const int GetScore() const { return m_currentScore; };
	const int GetCurrentLives() const { return m_currentLives; };
	const int GetMaxLives() const { return m_maxLives; };
	const int GetDifficultyLevel() const { return m_difficultyLevel; };
	const Vector2& GetPlayerStartPosition() const { return m_startPosition; };
	const bool GetIsPaused() const { return m_isPaused; };

	~GameState();

private:

	GameState();

	void IncreaseDifficulty();
	void GameOver();
	void UpdateHUD(const Player& player);
	void ResetGameState(Player& player);

	Vector2 m_startPosition;
	const int m_maxLives = 3;
	// Each amount score awarded, increases difficulty by 1
	const int m_scoreAmountToIncreseDiff = 20;
	int m_currentLives;
	int m_currentScore = 0;
	int m_highScore = 0;
	int m_difficultyLevel = 1;

	bool m_isPaused = false;

	HUD* m_hud = nullptr;

	Sound m_playerHit;

	static GameState* s_gameState;
};
