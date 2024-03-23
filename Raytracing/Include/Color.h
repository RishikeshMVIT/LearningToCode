#pragma once

#include <iostream>

#include "Vector3.h"

using Color = Vector3;

void WriteColor(std::ostream& out, Color pixelColor)
{
	out << static_cast<int>(255.99 * pixelColor.x()) << ' '
		<< static_cast<int>(255.99 * pixelColor.y()) << ' '
		<< static_cast<int>(255.99 * pixelColor.z()) << ' ';
}
