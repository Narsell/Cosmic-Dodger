#pragma once
#include <vector>

#include "userinterface/UIElement.hpp"
#include "userinterface/TextureRect.hpp"


class UIPlayerLives : public UIElement {

public:
	UIPlayerLives(const HUD* parentHud, const Transform& transform, const int maxLives, const char* name = "NA_PlayerLivesUI");

	void UpdateCurrentLives(const int currentLives);

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override {};

private:

	const int m_maxLives;
	int m_currentLives;
	const float m_paddingRight = 10;
	std::vector<UITextureRect*> m_lives;

};
