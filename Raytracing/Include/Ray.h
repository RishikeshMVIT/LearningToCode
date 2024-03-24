#pragma once

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Point3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction) {}

	Point3 Origin() const { return m_origin; }
	Vector3 Direction() const { return m_direction; }

	Point3 At(float translation) const
	{
		return m_origin + (translation * m_direction);
	}

private:
	Point3 m_origin;
	Vector3 m_direction;
};
