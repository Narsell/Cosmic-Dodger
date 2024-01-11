#pragma once

class GameState {

public:
	~GameState();

private:
	GameState();

	const int m_maxLives = 3;
	int m_currentLives;
	int m_currentScore = 0;
};
