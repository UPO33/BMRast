#pragma once

#include <math.h>
#include <memory>
#include "Int2.h"


inline unsigned UBGRAColor(uint8_t b, uint8_t g, uint8_t r, uint8_t a)
{
	union 
	{
		uint8_t bgra[4];
		unsigned color;
	};

	bgra[0] = b;
	bgra[1] = g;
	bgra[2] = r;
	bgra[3] = a;

	return color;
}
class CSurface
{
	unsigned mWidth;
	unsigned mHeight;
	//rest are pixels

	CSurface(){}
	CSurface(unsigned w, unsigned h) : mWidth(w), mHeight(h) {}

public:

	typedef unsigned ColorT;

	static CSurface* Create(unsigned w, unsigned h)
	{
		 void* pSurface = ::malloc(sizeof(CSurface) +  (w * h * sizeof(ColorT)));
		 return new (pSurface) CSurface(w, h);
	}
	static void Delete(CSurface* pSurface)
	{
		::free(pSurface);
	}

	unsigned Width() const { return mWidth; }
	unsigned Height() const { return mHeight; }
	
	ColorT* GetPixels() const
	{
		return (ColorT*)(this + 1);
	}
	ColorT* GetPixel(unsigned x, unsigned y) const
	{
		return GetPixels() + y * mWidth + x;
	}
	unsigned GetImageSizeInBytes() const
	{
		return mWidth * mHeight * sizeof(ColorT);
	}
	void Fill(ColorT color)
	{
		memset(GetPixels(), color, GetImageSizeInBytes());
	}
	void DrawLine(int x0, int y0, int x1, int y1, ColorT color);
	void FillCircle(unsigned x, unsigned y, unsigned radius, ColorT color);
	void FillRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned rotationDegree, unsigned originX, unsigned originY);

};
