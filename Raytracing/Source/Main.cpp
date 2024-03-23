

#include <iostream>

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"


int main()
{
	std::cout << "Hello World";

	const unsigned int imageWidth = 256;
	const unsigned int imageHeight = 256;

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; j++)
	{
		std::clog << "/rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; i++)
		{
			auto pixelColor = Color(float(i) / (imageWidth - 1), float(j) / (imageHeight - 1), 0);
			WriteColor(std::cout, pixelColor);
		}
	}

	std::clog << "\rDone";

	return 0;
}
