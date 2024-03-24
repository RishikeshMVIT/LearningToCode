#pragma once

#include "Vector3.h"
#include "Ray.h"

class HitRecord
{
public:
	Point3 hitPoint;
	Vector3 normal;
	float interval;
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
};
