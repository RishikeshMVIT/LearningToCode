#pragma once

#include <iostream>

#include "Vector3.h"

// Alias for representing colors
using Color = Vector3;

inline double LinearToGamma(double linearComponent) { return sqrt(linearComponent); }

void WriteColor(std::ostream& out, Color pixelColor, int samplesPerPixel)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	auto scale = 1.0 / samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Linear to Gamma Transform
	r = LinearToGamma(r);
	g = LinearToGamma(g);
	b = LinearToGamma(b);
	
	static const Interval intensity(0.000, 0.999);

	out << static_cast<int>(255.99 * intensity.Clamp(r)) << ' '
		<< static_cast<int>(255.99 * intensity.Clamp(g)) << ' '
		<< static_cast<int>(255.99 * intensity.Clamp(b)) << '\n';
}
