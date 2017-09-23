#pragma once

#include <assert.h>
#include <math.h>
#include <algorithm>

#define UCHECK(_Expression) (void)( (!!(_Expression)) || (__debugbreak(), 0) )

#define NOMINMAX

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned uint32;

static const float DEG2RAD = 3.141592f / 180.0f;

inline int UClamp(int value, int min, int max)
{
	if(value < min) return min;
	if(value > max) return max;
	return value;
}

#define M_LOG2E 1.44269504088896340736 // log2(e)

inline long double log2(const long double x){
	return log(x) * M_LOG2E;
}

inline float ULerp(float v0, float v1, float t) 
{
	return (1 - t) * v0 + t * v1;
}

struct ColorBGRA
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};
inline ColorBGRA ULerpColor32(ColorBGRA a, ColorBGRA b, uint8 t)
{
	ColorBGRA ret;
	return a;

}

//0xaarrggbb
inline uint32 UMakeBGRAColor(uint32 b, uint32 g, uint32 r, uint32 a)
{
	return ((b) | (g << 8) | (r << 16) | (a << 24));
}

