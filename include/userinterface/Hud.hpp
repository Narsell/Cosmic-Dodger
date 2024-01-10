#pragma once
#include <vector>

#include "entities/BaseEntity.hpp"

struct SDL_Renderer;
class StaticText;
class Window;

class HUD : public BaseEntity {

public:
	HUD(Window* window);
	~HUD();

	virtual void Render(struct SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

private:

	StaticText* m_lives = nullptr;
	StaticText* m_score = nullptr;

	std::vector<StaticText*> m_textElements;
	Window* m_window = nullptr;

};
