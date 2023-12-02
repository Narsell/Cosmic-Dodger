#pragma once

class BaseEntity {

public:

	virtual ~BaseEntity() {};

	bool operator!() {
		return this == nullptr;
	}

	bool GetIsVisible() const { return m_isVisible; };
	bool GetCanUpdate() const { return m_canUpdate; };

	void SetCanRender(const bool canRender) { m_isVisible = canRender; };
	void SetCanUpdate(const bool canUpdate) { m_canUpdate = canUpdate; };

protected:

	BaseEntity();
	BaseEntity(const char* entityId, const char* entityName, const bool canRender=false, const bool canUpdate=true);

	virtual void Render(struct SDL_Renderer* renderer) = 0;
	virtual void Update(const float deltaTime) = 0;


protected:

	bool m_isVisible = false;
	bool m_canUpdate = true;

private:

	const char* m_id = "";
	const char* m_displayName = "NA_BaseEntity";

};
