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
    m_player = dynamic_cast<Player*>(m_parent);
    assert(m_player);
}

void PlayerInputComponent::Update(const float deltaTime)
{

	m_eventQueue = GameManager::GetInputEventQueue();
	m_keyboardState = GameManager::GetInputKeyboardState();

	assert(m_keyboardState);

	for (SDL_Event& frameEvent : m_eventQueue) {
		if (frameEvent.type == SDL_MOUSEBUTTONDOWN && frameEvent.button.button == SDL_BUTTON_LEFT){
			m_isShooting = true;
		}
		else if (frameEvent.type == SDL_MOUSEBUTTONUP && frameEvent.button.button == SDL_BUTTON_LEFT) {
			m_isShooting = false;
		}
	}

	if (m_keyboardState[SDL_SCANCODE_M])
	{
		std::cout << AllocationMetrics::GetInstance()->CurrentUsage() << std::endl;
	}


	if (m_isShooting)
		m_player->ShootProjectile();

	m_player->SetCanMove(m_keyboardState[SDL_SCANCODE_W]);
}
