#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double UINFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double TAU = PI * 2;

// Converts Degrees to Radians
inline double DegreesToRadians(double degrees) { return degrees * PI / 180.0; }

// Random double between [0,1)
inline double RandomDouble() { return rand() / (RAND_MAX + 1.0); }

// Random double in between min and max
inline double RandomDouble(double min, double max) { return min + (max - min) * RandomDouble(); }

#include "Interval.h"
#include "Ray.h"
#include "Vector3.h"
