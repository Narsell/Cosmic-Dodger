#pragma once
#include <vector>

#include "userinterface/UIElement.hpp"
#include "userinterface/UIProgressTextures.hpp"
#include "userinterface/UIStaticText.hpp"
#include "userinterface/DeathMenu.hpp"

struct SDL_Renderer;
class Window;

enum HUD_STATE {
	PLAYING,
	DEAD
};

class HUD : public UIElement {

public:
	HUD();
	~HUD();

	void SetState(HUD_STATE state);

	void UpdateDeathMenu(const int currentScore, const int difficulty);
	void UpdateLives(const int lives);
	void UpdateScore(const int score);
	void UpdateHighScore(const int highScore);
	void UpdateAmmo(const int ammo);
	void UpdateDifficultyLevel(const int difficultyLevel);

	virtual void Render(struct SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

private:

	UIProgressTextures m_livesProgress;
	UIProgressTextures m_ammoProgress;

	UIStaticText m_score;
	UIStaticText m_highScore;
	UIStaticText m_difficultyLevel;

	DeathMenu m_deathMenu;

	//std::vector<UIElement&> m_uiElements;


};
