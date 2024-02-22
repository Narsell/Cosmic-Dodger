#include "userinterface/DeathMenu.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/Color.hpp"


DeathMenu::DeathMenu(const Transform& transform, const char* name)
	:UIElement(transform, name),
	m_background(*ResourceManager::uiBackgroundTexture, Transform(Vector2(-ResourceManager::uiBackgroundTexture->GetDimensions().x / 2.f, -ResourceManager::uiBackgroundTexture->GetDimensions().y/2.f))),
	m_title("YOU LOST!", Color(255, 0, 160), Transform(Vector2((ResourceManager::uiBackgroundTexture->GetDimensions().x / 2.f) - 240.f/2.f, 50)), Vector2(240.f, 60.f)),
	m_score("SCORE: 0", Color::black, Transform(Vector2((ResourceManager::uiBackgroundTexture->GetDimensions().x / 2.f) - 200.f / 2.f, 150.f)), Vector2(200.f, 50.f)),
	m_level("LEVEL: 1", Color::black, Transform(Vector2((ResourceManager::uiBackgroundTexture->GetDimensions().x / 2.f) - 180.f / 2.f, 200.f)), Vector2(180.f, 50.f))
{
	AddChild(&m_background);
	m_background.AddChild(&m_title);
	m_background.AddChild(&m_score);
	m_background.AddChild(&m_level);
}

DeathMenu::~DeathMenu()
{
}

void DeathMenu::UpdateValues(const int currentScore, const int difficulty)
{
	m_score.SetText("SCORE: " + std::to_string(currentScore));
	m_level.SetText("LEVEL: " + std::to_string(difficulty));
}

void DeathMenu::Render(SDL_Renderer* renderer)
{
	UIElement::Render(renderer);
}

void DeathMenu::Update(const float deltaTime)
{
	UIElement::Update(deltaTime);
}
