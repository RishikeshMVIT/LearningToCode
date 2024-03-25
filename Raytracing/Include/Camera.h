#pragma once

#include <iostream>

#include "MathUtils.h"
#include "Color.h"
#include "Hittable.h"

class Camera
{
public:
	void Render(const Hittable& world)
	{
		Initialize();

		std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = 0; j < imageHeight; j++)
		{
			std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
			for (int i = 0; i < imageWidth; i++)
			{
				Color pixelColor(0, 0, 0);
				for (int sample = 0; sample < samplesPerPixel; ++sample)
				{
					Ray ray = GetRay(i, j);
					pixelColor += RayColor(ray, world, maxDepth);
				}

				WriteColor(std::cout, pixelColor, samplesPerPixel);
			}
		}

		std::clog << "\rDone			\n";
	}

private:
	void Initialize()
	{
		imageHeight = static_cast<int>(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		center = Point3(0, 0, 0);

		auto focalLength = 1.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
		
		// Horizontal and Vertical Viewport Vectors
		auto viewportU = Vector3(viewportWidth, 0, 0);
		auto viewportV = Vector3(0, -viewportHeight, 0);

		// Pixel Delta
		pixelDeltaU = viewportU / imageWidth;
		pixelDeltaV = viewportV / imageHeight;

		auto viewportUpperLeft = center - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
		pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
	}

	Vector3 pixelSampleSquare()
	{
		auto px = -0.5 + RandomDouble();
		auto py = -0.5 + RandomDouble();

		return (px * pixelDeltaU) + (py * pixelDeltaV);
	}

	Vector3 pixelSampleDisk()
	{
		return Vector3();
	}

	Ray GetRay(int i, int j)
	{
		auto pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
		auto pixelSample = pixelCenter + pixelSampleSquare();

		auto rayOrigin = center;
		auto rayDirection = pixelSample - rayOrigin;

		return Ray(rayOrigin, rayDirection);
	}

	Color RayColor(const Ray& ray, const Hittable& world, int depth) const
	{
		HitRecord record;

		if (depth <= 0)
			return Color(0, 0, 0);

		if (world.Hit(ray, Interval(0.001, UINFINITY), record))
		{
			Vector3 direction = RandomVectorOnHemisphere(record.normal);
			return 0.5 * RayColor(Ray(record.hitPoint, direction), world, depth - 1);
		}

		Vector3 unitDirection = UnitVector(ray.Direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}

public:
	double aspectRatio = 1.0;
	int imageWidth = 100;
	int samplesPerPixel = 10;
	int maxDepth = 10;

private:
	int imageHeight;
	Point3 center;
	Point3 pixel00Location;
	Vector3 pixelDeltaU;
	Vector3 pixelDeltaV;
};