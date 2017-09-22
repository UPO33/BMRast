#pragma once

#include <math.h>
#include <memory>
#include "Int2.h"


inline unsigned UBGRAColor(uint8_t b, uint8_t g, uint8_t r, uint8_t a)
{
	return 0;
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
	void DrawLine(unsigned x0, unsigned y0, unsigned x1, unsigned y1, ColorT color)
	{
		int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2, e2;

		for (;;)
		{
			*GetPixel(x0, y0) = color;

			if (x0 == x1 && y0 == y1)
				break;
			e2 = err;
			if (e2 > -dx)
			{
				err -= dy; x0 += sx;
			}
			if (e2 < dy)
			{
				err += dx; y0 += sy;
			}
		}
	}
	void DrawRectSolid(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color)
	{
		w = min(w, mWidth);
		h = min(h, mHeight);

		for (; y < h; y++)
		{
			for (; x < w; x++)
			{
				*GetPixel(x, y) = color;
			}
		}
	}
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h)
	{

	}
	void DrawSurfaceRotated(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h, unsigned rotationInDegrees)
	{

	}

};
