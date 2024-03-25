#pragma once

#include "Hittable.h"
#include "Vector3.h"

class SphereSDF : public Hittable
{
public:
	SphereSDF(Point3 center, double radius) : m_center(center), m_radius(radius) {}

	bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override
	{
		Vector3 oc = ray.Origin() - m_center;
		auto a = ray.Direction().Length2();
		auto h = Dot(oc, ray.Direction());
		auto c = oc.Length2() - (m_radius * m_radius);

		auto discriminant = (h * h) - (a * c);
		if (discriminant < 0)
			return false;
		auto sqrtDisc = sqrt(discriminant);

		auto root = (-h - sqrtDisc) / a;
		if (root <= tMin || tMax <= root)
		{
			root = (-h + sqrtDisc) / a;
			if (root <= tMin || tMax <= root)
			{
				return false;
			}
		}

		record.interval = root;
		record.hitPoint = ray.At(record.interval);
		Vector3 outwardNormal = (record.hitPoint - m_center) / m_radius;
		record.SetFaceNormal(ray, outwardNormal);

		return true;
	}

private:
	Point3 m_center;
	double m_radius;
};