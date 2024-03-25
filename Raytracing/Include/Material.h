#pragma once

#include "MathUtils.h"
#include "Color.h"
#include "Hittable.h"

class Material
{
public:
	virtual ~Material() = default;

	virtual bool Scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

class LambertianMaterial : public Material
{
public:
	LambertianMaterial(const Color& color) : albedo(color) {}

	bool Scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
	{
		auto scatterDirection = record.normal + RandomUnitVector();

		if (scatterDirection.NearZero())
			scatterDirection = record.normal;

		scattered = Ray(record.hitPoint, scatterDirection);
		attenuation = albedo;
		return true;
	}

private:
	Color albedo;
};

class MetallicMaterial : public Material
{
public:
	MetallicMaterial(const Color& color, double fuzzAmount) : albedo(color), fuzz(fuzzAmount) {}

	bool Scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
	{
		Vector3 reflected = Reflect(UnitVector(ray.Direction()), record.normal);
		scattered = Ray(record.hitPoint, reflected + fuzz * RandomUnitVector());
		attenuation = albedo;
		return (Dot(scattered.Direction(), record.normal) > 0);
	}

private:
	Color albedo;
	double fuzz;
};

class DielectricMaterial : public Material
{
public:
	DielectricMaterial(double refractionIndex) : ior(refractionIndex) {};

	bool Scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
	{
		attenuation = Color(1.0, 1.0, 1.0);
		double refractionRatio = record.isFrontFace ? (1.0 / ior) : ior;

		Vector3 unitDirection = UnitVector(ray.Direction());

		double cosine = fmin(Dot(-unitDirection, record.normal), 1.0);
		double sine = sqrt(1.0 - (cosine * cosine));

		bool cannotRefract = refractionRatio * sine > 1.0;
		Vector3 direction;
		if (cannotRefract || Reflectance(cosine, refractionRatio) > RandomDouble())
			direction = Reflect(unitDirection, record.normal);
		else
			direction = Refract(unitDirection, record.normal, refractionRatio);

		scattered = Ray(record.hitPoint, direction);
		return true;
	}
private:
	static double Reflectance(double cosine, double refIDX)
	{
		auto r0 = (1 - refIDX) / (1 + refIDX);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

private:
	double ior; // Index Of Refraction
};
