#pragma once
#include <vector>

#include "entities/BaseEntity.hpp"

struct SDL_Renderer;
class StaticText;
class GameState;
class Window;

class HUD : public BaseEntity {

public:
	HUD(Window* window);
	~HUD();

	void UpdateLives(const int lives);
	void UpdateScore(const int score);
	void UpdateHighScore(const int highScore);
	void UpdateAmmo(const int ammo);

	virtual void Render(struct SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

	Window* GetTargetWindow() const { return m_window; };

private:
	Window* m_window;

	StaticText* m_lives;
	StaticText* m_score;
	StaticText* m_highScore;
	StaticText* m_ammo;

	std::vector<StaticText*> m_textElements;


};
