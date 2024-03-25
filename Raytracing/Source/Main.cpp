

#include <iostream>

#include "MathUtils.h"
#include "Camera.h"
#include "Color.h"
#include "Hittable.h"
#include "HIttableList.h"
#include "SphereSDF.h"


int main()
{
	std::clog << "Hello World";

	// Image
	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;
	int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	// World
	HittableList world;
	world.Add(make_shared<SphereSDF>(Point3(0, 0, -1), 0.5));
	world.Add(make_shared<SphereSDF>(Point3(0, -100.5, -1), 100));

	// Camera
	Camera camera;
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;
	camera.maxDepth = 50;

	camera.Render(world);

	return 0;
}
