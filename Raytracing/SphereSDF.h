#pragma once

#include "Hittable.h"
#include "Vector3.h"

class SphereSDF : public Hittable
{
public:
	SphereSDF(Point3 center, float radius) : m_center(center), m_radius(radius) {}

	bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override
	{


		return true;
	}

private:
	Point3 m_center;
	float m_radius;
};
