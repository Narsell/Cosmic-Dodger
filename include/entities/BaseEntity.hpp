#pragma once

class BaseEntity {

public:

	virtual ~BaseEntity() {};

	bool operator!() {
		return this == nullptr;
	}

protected:

	BaseEntity();
	BaseEntity(const char* entityId, const char* entityName);
	virtual void Update(const float deltaTime) = 0;

private:

	const char* m_id = "";
	const char* m_displayName = "NA_BaseEntity";
};
