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

	Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

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

	Vector3& operator/=(double scale)
	{
		return *this *= (1 / scale);
	}

	double Length2() const
	{
		return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
	}

	double Length() const
	{
		return sqrt(Length2());
	}
};

using Point3 = Vector3;

// Vector utility functions

inline std::ostream& operator<<(std::ostream& out, const Vector3& a)
{
	return out << a.e[0] << ' ' << a.e[1] << ' ' << a.e[2];
}

inline Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]);
}

inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]);
}

inline Vector3 operator*(const Vector3& a, const Vector3& b)
{
	return Vector3(a.e[0] * b.e[0], a.e[1] * b.e[1], a.e[2] * b.e[2]);
}

inline Vector3 operator*(double scale, const Vector3& a)
{
	return Vector3(a.e[0] * scale, a.e[1] * scale, a.e[2] * scale);
}

inline Vector3 operator*(const Vector3& a, double scale)
{
	return scale * a;
}

inline Vector3 operator/(double scale, const Vector3& a)
{
	return (1 / scale) * a;
}

inline Vector3 operator/(const Vector3& a, double scale)
{
	return (1 / scale) * a;
}

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

inline Vector3 UnitVector(Vector3 a)
{
	return a / a.Length();
}
