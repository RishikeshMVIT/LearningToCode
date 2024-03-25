#pragma once

#include <iostream>
#include <cmath>

class Vector3
{
public:
	double e[3];

	Vector3() : e{0,0,0} {}
	Vector3(double x, double y, double z) : e{x, y, z} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	Vector3 operator-()			const { return Vector3(-e[0], -e[1], -e[2]); }

	double  operator[](int i)	const { return e[i]; }
	double& operator[](int i)		  { return e[i]; }

	Vector3& operator+=(const Vector3& other)
	{
		e[0] += other.e[0];
		e[1] += other.e[1];
		e[2] += other.e[2];
		return *this;
	}
	Vector3& operator*=(double scale)
	{
		e[0] *= scale;
		e[1] *= scale;
		e[2] *= scale;
		return *this;
	}
	Vector3& operator/=(double scale) { return *this *= (1 / scale); }

	double Length2() const { return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]); }
	double Length()  const { return sqrt(Length2()); }

	static Vector3 Random()						  { return Vector3(RandomDouble(), RandomDouble(), RandomDouble()); }
	static Vector3 Random(double min, double max) { return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)); }
	bool NearZero() const
	{
		auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}
};

// Alias for points in space
using Point3 = Vector3;

// Vector Utility Functions
inline std::ostream& operator<<(std::ostream& out, const Vector3& a) { return out << a.e[0] << ' ' << a.e[1] << ' ' << a.e[2]; }

inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]); }
inline Vector3 operator*(const Vector3& a, const Vector3& b) { return Vector3(a.e[0] * b.e[0], a.e[1] * b.e[1], a.e[2] * b.e[2]); }
inline Vector3 operator*(double scale, const Vector3& a)	 { return Vector3(a.e[0] * scale, a.e[1] * scale, a.e[2] * scale); }
inline Vector3 operator*(const Vector3& a, double scale)	 { return scale * a; }
inline Vector3 operator/(double scale, const Vector3& a)	 { return (1 / scale) * a; }
inline Vector3 operator/(const Vector3& a, double scale)	 { return (1 / scale) * a; }

inline double Dot(const Vector3& a, const Vector3& b)
{
	return a.e[0] * b.e[0]
		+ a.e[1] * b.e[1]
		+ a.e[2] * b.e[2];
}
inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3((a.e[1] * b.e[2]) - (a.e[2] * b.e[1]),
				   (a.e[2] * b.e[0]) - (a.e[0] * b.e[2]),
				   (a.e[0] * b.e[1]) - (a.e[1] * b.e[0]));
}

inline Vector3 UnitVector(Vector3 a) { return a / a.Length(); }
inline Vector3 RandomVectorInUnitDisk()
{
	while (true)
	{
		auto p = Vector3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
		if (p.Length2() < 1)
			return p;
	}
}
inline Vector3 RandomVectorInUnitSphere()
{
	while (true)
	{
		auto p = Vector3::Random(-1, 1);
		if (p.Length2() < 1)
			return p;
	}
}
inline Vector3 RandomUnitVector() { return UnitVector(RandomVectorInUnitSphere()); }
inline Vector3 RandomVectorOnHemisphere(const Vector3& normal)
{
	Vector3 onUnitSphere = RandomUnitVector();
	if (Dot(onUnitSphere, normal) > 0.0) 
		return onUnitSphere;
	else 
		return -onUnitSphere;
}

// Reflect a vector about another
Vector3 Reflect(const Vector3& a, const Vector3& b) { return a - (2 * Dot(a, b) * b); }
//Refraction of a vector about a normal
Vector3 Refract(const Vector3& a, const Vector3& b, double iorRatio)
{
	auto cosine = fmin(Dot(-a, b), 1.0);
	Vector3 refractedRayPerpendicular = iorRatio * (a + cosine * b);
	Vector3 refractedRayParallel = -sqrt(fabs(1.0 - refractedRayPerpendicular.Length2())) * b;
	return refractedRayParallel + refractedRayPerpendicular;
}
//TODO: Analytical Methods to manipulate a random vector so that the results are on the surface of a hemisphere
//		Currently using Rejection Method - repeatedly generating until a sample which meets the desired criteria
//		>> Generate Vector inside unit sphere > Normaize > Invert if it falls on wrong hemisphere;
