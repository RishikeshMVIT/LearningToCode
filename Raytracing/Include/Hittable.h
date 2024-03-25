#pragma once

#include "Vector3.h"
#include "Ray.h"

class HitRecord
{
public:
	Point3 hitPoint;
	Vector3 normal;
	double interval;
	bool isFrontFace;

	void SetFaceNormal(const Ray& ray, const Vector3& out)
	{
		isFrontFace = Dot(ray.Direction(), out) < 0;
		normal = isFrontFace ? out : -out;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};
