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

	m_player->SetCanMove(m_keyboardState[SDL_SCANCODE_W]);
}
