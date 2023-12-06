#pragma once

class BaseEntity {

public:

	virtual ~BaseEntity();

	bool operator!() {
		return this == nullptr;
	}

	virtual void Render(struct SDL_Renderer* renderer);
	virtual void Update(const float deltaTime) = 0;

	bool GetCanRender() const { return m_canRender; };
	bool GetCanUpdate() const { return m_canUpdate; };

	void SetCanRender(const bool canRender) { m_canRender = canRender; };
	void SetCanUpdate(const bool canUpdate) { m_canUpdate = canUpdate; };

	const char* GetDisplayName() const { return m_displayName; };

protected:

	BaseEntity();
	BaseEntity(const char* entityId, const char* entityName, const bool canRender=false, const bool canUpdate=true);

protected:

	bool m_canRender = false;
	bool m_canUpdate = true;

private:

	const char* m_id = "";
	const char* m_displayName = "NA_BaseEntity";

};
