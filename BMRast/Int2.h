#pragma once

#include "Utility.h"
#include <iostream>
#include <algorithm>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

struct Int2
{
	int x, y;

	Int2() {}
	Int2(int xx, int yy) : x(xx), y(yy) {}

	static Int2 Min(Int2 a, Int2 b)
	{
		return Int2(std::min(a.x, b.x), std::min(a.y, b.y));
	}
	static Int2 Max(Int2 a, Int2 b)
	{
		return Int2(std::max(a.x, b.x), std::max(a.y, b.y));
	}
};

inline Int2 operator + (Int2 l, Int2 r)
{
	return Int2(l.x + r.x, l.y + r.y);
}
inline Int2 operator - (Int2 l, Int2 r)
{
	return Int2(l.x - r.x, l.y - r.y);
}
inline Int2 operator * (Int2 l, Int2 r)
{
	return Int2(l.x * r.x, l.y * r.y);
}
inline Int2 operator / (Int2 l, Int2 r)
{
	return Int2(l.x / r.x, l.y / r.y);
}

inline std::ostream& operator << (std::ostream& os, Int2 rValue)
{
	os << "{" << rValue.x << ", " << rValue.y << "}";
	return os;
}
#define ZZInt2CmpInt2(op)\
	inline bool operator op (Int2 l, Int2 r)\
{\
	return l.x op r.x && l.y op r.y;\
}\

ZZInt2CmpInt2(>)
ZZInt2CmpInt2(<)
ZZInt2CmpInt2(>=)
ZZInt2CmpInt2(<=)



inline Int2 URotatePoint(int x, int y, float s, float c)
{
	float xnew = x * c - y * s;
	float ynew = x * s + y * c;
	return Int2(xnew, ynew);
}
inline Int2 URotatePointInt(int x, int y, int s, int c)
{
	return Int2(
		x * c - y * s,
		x * s + y * c);
}
inline Int2 URotatePoint(int x, int y, float s, float c, int cx, int cy)
{
	Int2 p;
	p.x = x - cx;
	p.y = y - cy;

	// rotate point
	//float xnew = p.x * c + p.y * s;
	//float ynew = p.y * c - p.x * s;
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}
inline Int2 URotatePoint(Int2 p, float angle, int cx, int cy)
{
	float s = sin(angle);
	float c = cos(angle);

	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}

inline Int2 UGetLineNormal(Int2 a, Int2 b)
{
	Int2 delta = b - a;
	return Int2(-delta.y, delta.x);
}