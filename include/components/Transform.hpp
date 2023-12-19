#pragma once

#include "Math.hpp"

class Transform {

public:

	Transform(const Vector2& position = Vector2::ZERO, const double rotation = 0.0, const double scale=1.0) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{};

	const Vector2& GetPosition() const { return m_position; };
	const double GetRotation() const { return m_rotation; };
	const double GetScale() const { return m_scale; };

	void SetPosition(const Vector2& newPosition) { m_position = newPosition; };
	void SetRotation(const double newRotation) { m_rotation = newRotation; };
	void SetScale(const float newScale) { m_scale = newScale; };

private:

	Vector2 m_position = Vector2::ZERO;
	double m_rotation = 0.0;
	double m_scale = 1.0;
};