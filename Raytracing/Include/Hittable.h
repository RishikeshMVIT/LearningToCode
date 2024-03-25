#pragma once

#include "MathUtils.h"
#include "Vector3.h"
#include "Ray.h"

class Material;

class HitRecord
{
public:
	void SetFaceNormal(const Ray& ray, const Vector3& out)
	{
		isFrontFace = Dot(ray.Direction(), out) < 0;
		normal = isFrontFace ? out : -out;
	}

public:
	Point3  hitPoint;
	Vector3 normal;
	double  interval;
	bool    isFrontFace;
	shared_ptr<Material> material;
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const Ray& ray, Interval interval, HitRecord& record) const = 0;
};
