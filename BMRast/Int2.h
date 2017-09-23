#pragma once


struct Int2
{
	int x, y;

	Int2() {}
	Int2(int xx, int yy) : x(xx), y(yy) {}
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


