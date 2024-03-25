#pragma once

#include "Hittable.h"
#include "Vector3.h"

class SphereSDF : public Hittable
{
public:
	SphereSDF(Point3 center, double radius, shared_ptr<Material> material) 
		: m_center(center), m_radius(radius), m_material(material) {}

	bool Hit(const Ray& ray, Interval interval, HitRecord& record) const override
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
		if (!interval.Surrounds(root))
		{
			root = (-h + sqrtDisc) / a;
			if (!interval.Surrounds(root))
				return false;
		}

		record.interval = root;
		record.hitPoint = ray.At(record.interval);
		Vector3 outwardNormal = (record.hitPoint - m_center) / m_radius;
		record.SetFaceNormal(ray, outwardNormal);
		record.material = m_material;

		return true;
	}

private:
	shared_ptr<Material> m_material;
	Point3 m_center;
	double m_radius;
};
