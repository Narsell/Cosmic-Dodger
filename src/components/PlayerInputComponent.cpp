#include "SDL.h"
#include <iostream>
#include <assert.h>

#include "PlayerInputComponent.hpp"
#include "MovementComponent.hpp"
#include "GameManager.hpp"
#include "Player.hpp"
#include "Utils.hpp"

PlayerInputComponent::PlayerInputComponent(GameObject* parent, const char* name)
    :Component(parent, name),
    m_keyboardState(nullptr)
{
    GameManager::SuscribeToKeyboardEvents(this);
    m_player = dynamic_cast<Player*>(m_parent);
    assert(m_player);
}

void PlayerInputComponent::Update(const float deltaTime)
{
	assert(m_keyboardState);

	if (m_keyboardState[SDL_SCANCODE_SPACE]) {
		m_player->ShootProjectile();
	}

	if (m_keyboardState[SDL_SCANCODE_M])
	{
		std::cout << AllocationMetrics::GetInstance()->CurrentUsage() << std::endl;
	}

	if (m_keyboardState[SDL_SCANCODE_D] || m_keyboardState[SDL_SCANCODE_A] || m_keyboardState[SDL_SCANCODE_S] || m_keyboardState[SDL_SCANCODE_W]) {
		if (m_keyboardState[SDL_SCANCODE_D]){
			m_inputVector = Vector2::RIGHT;
		}
		if (m_keyboardState[SDL_SCANCODE_A]) {
			m_inputVector = Vector2::LEFT;
		}
		if (m_keyboardState[SDL_SCANCODE_W]) {
			m_inputVector = Vector2::UP;
		}
		if (m_keyboardState[SDL_SCANCODE_S]) {
			m_inputVector = Vector2::DOWN;
		}

	}
	else {
		m_inputVector = Vector2::ZERO;
	}

	m_player->GetMovementComponent()->SetVelocity(m_inputVector.Normalized());

}
