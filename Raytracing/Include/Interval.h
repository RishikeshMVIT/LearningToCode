#pragma once

class Interval
{
public:
	Interval() : min(+UINFINITY), max(-UINFINITY) {}
	Interval(double _min, double _max) : min(_min), max(_max) {}

	bool Contains(double x) const { return min <= x || x <= max; }
	bool Surrounds(double x) const { return min < x && x < max; }

	double Clamp(double x) const
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	static const Interval empty, universe;

public:
	double min, max;
};

const static Interval empty(+UINFINITY, -UINFINITY);
const static Interval universe(-UINFINITY, +UINFINITY);