#include "userinterface/DeathMenu.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/GameState.hpp"
#include "utilities/Color.hpp"


DeathMenu::DeathMenu(const Transform& transform, const char* name)
	:UIElement(transform, name),
	m_background(ResourceManager::uiBackgroundTexture, Transform(Vector2(-ResourceManager::uiBackgroundTexture->GetDimensions().x / 2.f, -ResourceManager::uiBackgroundTexture->GetDimensions().y/2.f))),
	m_title("YOU LOST!", Color(255, 0, 160), Transform(Vector2(-120.f, -175.f)), Vector2(240.f, 60.)),
	m_score("SCORE: 0", Color::black, Transform(Vector2(-100.f, -50.f)), Vector2(200.f, 50.f)),
	m_level("LEVEL: 1", Color::black, Transform(Vector2(-90.f, 0.f)), Vector2(180.f, 50.f)),
	m_button("TRY AGAIN", ResourceManager::uiButton, Transform(Vector2(-ResourceManager::uiButton->GetDimensions().x / 2.f, 100.f)))
{
	AddChild(&m_background);
	AddChild(&m_title);
	AddChild(&m_score);
	AddChild(&m_level);
	AddChild(&m_button);
	
	m_button.SetOnPressedDelegate(std::bind(&GameState::OnTryAgain, GameState::GetGameState()));
	m_button.m_transform.SetRotation(90.f);
	m_button.SetHoverTexture(ResourceManager::uiButtonHover);

	SetCanUpdate(true);
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
