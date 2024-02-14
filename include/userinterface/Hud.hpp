#pragma once
#include <vector>

#include "entities/BaseEntity.hpp"

struct SDL_Renderer;
class UIStaticText;
class UIElement;
class UIProgressTextures;
class Window;

class HUD : public BaseEntity {

public:
	HUD(Window* window);
	~HUD();

	void UpdateLives(const int lives);
	void UpdateScore(const int score);
	void UpdateHighScore(const int highScore);
	void UpdateAmmo(const int ammo);
	void UpdateDifficultyLevel(const int difficultyLevel);

	virtual void Render(struct SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

	Window* GetTargetWindow() const { return m_window; };

private:
	Window* m_window;

	UIProgressTextures* m_livesProgress = nullptr;
	UIProgressTextures* m_ammoProgress = nullptr;

	UIStaticText* m_score = nullptr;
	UIStaticText* m_highScore = nullptr;
	UIStaticText* m_difficultyLevel = nullptr;

	std::vector<UIElement*> m_uiElements;


};
