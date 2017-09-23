#pragma once

#include <assert.h>

#define UCHECK(_Expression) (void)( (!!(_Expression)) || (__debugbreak(), 0) )


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