#pragma once

#include "utilities/Math.hpp"

class Transform {

public:

	Transform(const Vector2& position = Vector2::ZERO, const float rotation = 0.0, const float scale=1.0) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{};

	const Vector2& GetPosition() const { return m_position; };
	const float GetRotation() const { return m_rotation; };
	const float GetScale() const { return m_scale; };

	void SetPosition(const Vector2& newPosition) { m_position = newPosition; };
	void SetRotation(const float newRotation);
	void SetScale(const float newScale) { m_scale = newScale; };

private:

	Vector2 m_position = Vector2::ZERO;
	float m_rotation = 0.f;
	float m_scale = 1.f;
};