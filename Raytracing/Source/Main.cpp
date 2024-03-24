

#include <iostream>

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

float HitSphere(const Point3& center, float radius, const Ray& ray)
{
	Vector3 oc = ray.Origin() - center;
	auto a = ray.Direction().Length2();
	auto h = Dot(oc, ray.Direction());
	auto c = oc.Length2() - (radius * radius);
	auto discriminant = (h * h) - (a * c);
	
	if (discriminant < 0)
		return -1.0;
	else
		return ((-h - sqrt(discriminant)) / a);
}

Color RayColor(const Ray& ray)
{
	auto t = HitSphere(Point3(0, 0, -1), 0.5, ray);
	if (t > 0.0)
	{
		Vector3 normal = UnitVector(ray.At(t) - Vector3(0, 0, -1));
		return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
	}

	Vector3 unitDirection = UnitVector(ray.Direction());
	auto a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
	std::clog << "Hello World";

	// Image
	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;
	int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	// Camera
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);
	auto cameraCenter = Point3(0, 0, 0);

	// Horizontal and Vertical Viewport Vectors
	auto viewportU = Vector3(viewportWidth, 0, 0);
	auto viewportV = Vector3(0, -viewportHeight, 0);

	// Pixel Delta
	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	// Location of Upper-Left Pixel
	auto viewportUpperLeft = cameraCenter - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
	auto pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; j++)
	{
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; i++)
		{
			auto pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;

			Ray r(cameraCenter, rayDirection);

			Color pixelColor = RayColor(r);

			WriteColor(std::cout, pixelColor);
		}
	}

	std::clog << std::flush << "\rDone			\n";

	return 0;
}
