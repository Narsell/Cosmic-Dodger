#pragma once

#include "Component.hpp"
#include "Math.hpp"

class GameObject;
class Player;

class PlayerInputComponent : public Component {

public:

	PlayerInputComponent(GameObject* parent, const char* name = "NA_PlayerInputComponent");

	virtual void Update(const float deltaTime) override;

	void UpdateKeyboardState(const Uint8* keyboardState) { m_keyboardState = keyboardState; };

private: 

	Player* m_player;
	const Uint8* m_keyboardState;

};
