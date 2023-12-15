#pragma once

#include "Math.hpp"

class Transform {

public:

	Transform(const Vector2& position = Vector2::ZERO, const float rotation = 0.f, const float scale=1.f) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{};

	const Vector2& GetPosition() const { return m_position; };
	const float GetRotation() const { return m_rotation; };
	const float GetScale() const { return m_scale; };

	void SetPosition(const Vector2& newPosition) { m_position = newPosition; };
	void SetRotation(const float newRotation) { m_rotation = newRotation; };
	void SetScale(const float newScale) { m_scale = newScale; };

private:

	Vector2 m_position;
	float m_rotation;
	float m_scale;
};