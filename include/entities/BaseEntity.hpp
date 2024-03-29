#pragma once
#include <sstream>
#include <iostream>

struct SDL_Renderer;

class BaseEntity {

public:

	BaseEntity(const BaseEntity& copy) = delete;
	const BaseEntity& operator=(const BaseEntity& other) = delete;
	virtual ~BaseEntity();

	bool operator!() {
		return this == nullptr;
	}

	bool GetCanRender() const { return m_canRender; };
	bool GetCanUpdate() const { return m_canUpdate; };

	virtual void Disable();
	virtual void Enable();
	virtual void SetCanRender(const bool canRender) { m_canRender = canRender; };
	virtual void SetCanUpdate(const bool canUpdate) { m_canUpdate = canUpdate; };

	const std::string& GetDisplayName() const { return m_displayName; };
	const std::string& GetIdName() const { return m_id; };

	void SetIdName(const std::string& idName) { m_id = idName; };

	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(const float deltaTime) = 0;

protected:

	BaseEntity(const char* entityId, const char* entityName, const bool canRender=false, const bool canUpdate=true);

protected:

	bool m_canRender = false;
	bool m_canUpdate = true;

private:

	std::string m_id = "";
	std::string m_displayName = "NA_BaseEntity";

};
