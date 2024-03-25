#pragma once

#include <iostream>

#include "MathUtils.h"
#include "Color.h"
#include "Hittable.h"
#include "Material.h"

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

		center = lookFrom;

		// Viewport Dimensions
		auto theta = DegreesToRadians(vFOV);
		auto h = tan(theta / 2);
		auto viewportHeight = 2.0 * h * focusDistance;
		auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

		// Camera Basis Vectors
		w = UnitVector(lookFrom - lookAt);
		u = UnitVector(Cross(upVector, w));
		v = Cross(w, u);
		
		// Horizontal and Vertical Viewport Vectors
		auto viewportU = viewportWidth * u;
		auto viewportV = viewportHeight * -v;

		// Pixel Delta
		pixelDeltaU = viewportU / imageWidth;
		pixelDeltaV = viewportV / imageHeight;

		auto viewportUpperLeft = center - (focusDistance * w) - viewportU / 2 - viewportV / 2;
		pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

		auto defocusRadius = focusDistance * tan(DegreesToRadians(defocusAngle / 2));
		defocusDiskU = u * defocusRadius;
		defocusDiskV = v * defocusRadius;
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

		auto rayOrigin = (defocusAngle <= 0) ? center : DefocusDiskSample();
		auto rayDirection = pixelSample - rayOrigin;

		return Ray(rayOrigin, rayDirection);
	}

	Point3 DefocusDiskSample() const
	{
		auto p = RandomVectorInUnitDisk();
		return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
	}

	Color RayColor(const Ray& ray, const Hittable& world, int depth) const
	{
		HitRecord record;

		// exceeded ray bounce limit, no more light can be accumulated
		if (depth <= 0)
			return Color(0, 0, 0);

		if (world.Hit(ray, Interval(0.001, UINFINITY), record))
		{
			Ray scattered;
			Color attenuation;
			if (record.material->Scatter(ray, record, attenuation, scattered))
				return attenuation * RayColor(scattered, world, depth - 1);
			return Color(0, 0, 0);
		}

		Vector3 unitDirection = UnitVector(ray.Direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}

public:
	double aspectRatio = 1.0;	// Ratio of image width over height
	int imageWidth = 100;		// Rendered image width in pixels
	int samplesPerPixel = 10;	// Number of random samples per pixel
	int maxDepth = 10;			// Max number of ray bounces
	double vFOV = 90;			// Vertica; Field of View
	Point3 lookFrom = Point3(0, 0, -1);
	Point3 lookAt = Point3(0, 0, 0);
	Vector3 upVector = Vector3(0, 1, 0);
	double defocusAngle = 0;
	double focusDistance = 10;

private:
	int imageHeight;
	Point3 center;
	Point3 pixel00Location;
	Vector3 pixelDeltaU, pixelDeltaV;
	Vector3 u, v, w;			// Camera Basis Vectors
	Vector3 defocusDiskU, defocusDiskV;
};