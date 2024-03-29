#pragma once

#include <memory>
#include <vector>

#include "Hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
	HittableList() {}
	HittableList(shared_ptr<Hittable> object) { Add(object); }

	void Clear() { objects.clear(); }
	void Add(shared_ptr<Hittable> object) { objects.push_back(object); }

	bool Hit(const Ray& ray, Interval interval, HitRecord& record) const override
	{
		HitRecord tempRecord;
		bool hasHit = false;
		auto closest = interval.max;

		for (const auto& object : objects)
		{
			if (object->Hit(ray, Interval(interval.min, closest), tempRecord))
			{
				hasHit = true;
				closest = tempRecord.interval;
				record = tempRecord;
			}
		}

		return hasHit;
	}

public:
	std::vector<shared_ptr<Hittable>> objects;
};
