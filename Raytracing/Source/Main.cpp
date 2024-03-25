

#include <iostream>

#include "MathUtils.h"
#include "Camera.h"
#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "SphereSDF.h"


int main()
{
	std::clog << "Hello World";

	auto materialGround = make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
	auto materialCenter = make_shared<LambertianMaterial>(Color(0.7, 0.3, 0.3));
	auto materialRight = make_shared<MetallicMaterial>(Color(0.8, 0.8, 0.8), 0.0);
	auto materialLeft = make_shared<DielectricMaterial>(1.5);

	// World
	HittableList world;
	world.Add(make_shared<SphereSDF>(Point3( 0, 0, -1), 0.5, materialCenter));
	world.Add(make_shared<SphereSDF>(Point3(-1, 0, -1), 0.5, materialLeft));
	world.Add(make_shared<SphereSDF>(Point3(-1, 0, -1), -0.4, materialLeft));
	world.Add(make_shared<SphereSDF>(Point3(1, 0, -1), 0.5, materialRight));
	world.Add(make_shared<SphereSDF>(Point3(0, -100.5, -1), 100, materialGround));

	// Camera
	Camera camera;
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;
	camera.maxDepth = 50;

	camera.vFOV = 20;
	camera.lookFrom = Point3(-2, 2, 1);
	camera.lookAt = Point3(0, 0, -1);
	camera.upVector = Vector3(0, 1, 0);

	camera.defocusAngle = 10.0;
	camera.focusDistance = 3.4;

	camera.Render(world);

	return 0;
}
