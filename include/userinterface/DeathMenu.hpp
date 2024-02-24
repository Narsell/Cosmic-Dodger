#pragma once
#include "userinterface/UIElement.hpp"
#include "userinterface/UITextureRect.hpp"
#include "userinterface/UIStaticText.hpp"
#include "userinterface/UIButton.hpp"

class DeathMenu : public UIElement {

public:
	DeathMenu(const Transform& transform, const char* name = "NA_DeathMenu");
	~DeathMenu();

	void UpdateValues(const int currentScore, const int difficulty);

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

private:

	UITextureRect m_background;
	UIStaticText m_title;
	UIStaticText m_score;
	UIStaticText m_level;
	UIButton m_button;

};
