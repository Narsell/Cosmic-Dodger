#pragma once
#include "SDL.h"
#include <vector>

#include "components/Component.hpp"
#include "utilities/Math.hpp"

class GameObject;
class Player;

class PlayerInputComponent : public Component {

public:

	PlayerInputComponent(GameObject* parent, const char* name = "NA_PlayerInputComponent");

	virtual void Update(const float deltaTime) override;

private: 

	Player* m_player;
	bool m_isShooting = false;
	std::vector<SDL_Event> m_eventQueue;
	const Uint8* m_keyboardState;

};
