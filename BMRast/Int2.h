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
	static Int2 Clamp(Int2 value, Int2 min, Int2 max)
	{
		return Int2(Min(Max(value, min), max));
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
inline Int2 operator *(Int2 l, float f)
{
	return Int2((int)(l.x * f), (int)(l.y * f));
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
inline Int2 URotatePoint(Int2 p, float angle, int cx = 0, int cy = 0)
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


struct Float2
{
	float x, y;

	Float2(){}
	explicit Float2(float _x, float _y) : x(_x), y(_y) {}
	Float2(Int2 xy) : x((float)xy.x), y((float)xy.y) {}

	operator Int2 () const
	{
		return Int2((int)x, (int)y);
	}
	float Length() const
	{
		return sqrt(x * x + y * y);
	}
	void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
	}
};

//////////////////////////////////////////////////////////////////////////Float2 op Float2
inline Float2 operator * (Float2 l , Float2 r)
{
	return Float2(l.x * r.x, l.y * r.y);
}
inline Float2 operator / (Float2 l , Float2 r)
{
	return Float2(l.x / r.x, l.y / r.y);
}
inline Float2 operator + (Float2 l , Float2 r)
{
	return Float2(l.x + r.x, l.y + r.y);
}
inline Float2 operator - (Float2 l , Float2 r)
{
	return Float2(l.x - r.x, l.y - r.y);
}
//////////////////////////////////////////////////////////////////////////Float2 op Float
inline Float2 operator * (Float2 l, float s)
{
	return Float2(l.x * s, l.y * s);
}
inline Float2 operator / (Float2 l, float s)
{
	return Float2(l.x / s, l.y / s);
}
inline Float2 operator + (Float2 l, float s)
{
	return Float2(l.x + s, l.y + s);
}
inline Float2 operator - (Float2 l, float s)
{
	return Float2(l.x - s, l.y - s);
}


struct Edge
{
	int X1, X2, Y1, Y2;

	explicit Edge(Int2 a, Int2 b)
	{
		if(a.y < b.y) 
		{
			X1 = a.x;
			Y1 = a.y;
			X2 = b.x;
			Y2 = b.y;
		} else
		{
			X1 = b.x;
			Y1 = b.y;
			X2 = a.x;
			Y2 = a.y;
		}
	}
	explicit Edge(int x1, int y1, int x2, int y2)
	{
		if(y1 < y2) 
		{
			X1 = x1;
			Y1 = y1;
			X2 = x2;
			Y2 = y2;
		} else
		{
			X1 = x2;
			Y1 = y2;
			X2 = x1;
			Y2 = y1;
		}
	}
};