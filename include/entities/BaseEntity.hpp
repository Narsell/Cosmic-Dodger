#pragma once

class BaseEntity {

public:

	virtual void Update(const float deltaTime) = 0;
	virtual ~BaseEntity() {};

	bool operator!() {
		return this == nullptr;
	}

private:

	const char* m_id = "0";
	const char* m_displayName = "NA";
};
