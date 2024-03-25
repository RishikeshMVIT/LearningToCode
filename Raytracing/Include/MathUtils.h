#pragma once

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double Utils_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double TAU = PI * 2;

inline double DegreesToRadians(double degrees)
{
	return degrees * PI / 180.0;
}

#include "Ray.h"
#include "Vector3.h"