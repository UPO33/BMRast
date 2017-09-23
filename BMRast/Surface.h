#pragma once

#include <math.h>
#include <memory>

#include "Utility.h"
#include "Int2.h"


enum EPixelFormat
{
	EPF_BGRA_UINT32
};

inline unsigned UBGRAColor(uint8 b, uint8 g, uint8 r, uint8 a)
{
	union 
	{
		uint8 bgra[4];
		unsigned color;
	};

	bgra[0] = b;
	bgra[1] = g;
	bgra[2] = r;
	bgra[3] = a;

	return color;
}
//////////////////////////////////////////////////////////////////////////
class CSurface
{
	unsigned mWidth;
	unsigned mHeight;
	EPixelFormat mPixelFormat;

	//rest are pixels

	CSurface(){}
	CSurface(unsigned w, unsigned h, EPixelFormat format = EPF_BGRA_UINT32) : mWidth(w), mHeight(h), mPixelFormat(format) {}

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
	ColorT* GetPixel(int x, int y) const
	{
		UCHECK(x >= 0 && y >= 0);
		UCHECK(x < mWidth && y < mHeight);
		return GetPixels() + (y * mWidth + x);
	}
	ColorT* GetPixel(Int2 xy) const
	{
		return GetPixel(xy.x, xy.y);
	}
	
	unsigned GetImageSizeInBytes() const
	{
		return mWidth * mHeight * sizeof(ColorT);
	}
	void Fill(ColorT color)
	{
		FillRect(0,0,mWidth, mHeight, color);
	}
	void FillMandelbortFractal();
	void FillRnadom();
	void FillGradient();

	//returns true in the specified point is inside the bitmap
	bool IsInBound(int x, int y)
	{
		return x >= 0 && x < mWidth && y >= 0 && y < mHeight;
	}
	//set pixel color without cheeking bound
	void SetPixelUnsafe(int x, int y, ColorT color)
	{
		*GetPixel(x, y) = color;
	}
	void SetPixel(int x, int y, ColorT color)
	{
		if(x < 0 || x >= mWidth 
			|| y < 0 || y >= mHeight) return;
		*GetPixel(x, y) = color;
	}
	void SetPixel(int x, int y, int penSize, ColorT color);


	void DrawHorizontalLine(int x0, int x1, int y, int thickness, ColorT color);
	void DrawVerticalLine(int y0, int y1, int x, int thickness, ColorT color);
	void DrawLineAA(int x1, int y1, int x2, int y2, ColorT color);
	void DrawLineAA(Int2 a, Int2 b, ColorT color) 
	{
		DrawLineAA(a.x, a.y, b.x, b.y, color);
	}
	void DrawLineAA(Int2 a, Int2 b, ColorT color, int thickness);

	void DrawLine(int x1, int y1, int x2, int y2, unsigned thickness, ColorT color);

	void DrawGradientLine(Int2 a, Int2 b, unsigned thickness, ColorT color);
	void BlendRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color);
	//void DrawLine(int x0, int y0, int x1, int y1, ColorT color);
	void FillCircle(unsigned x, unsigned y, unsigned radius, ColorT color);
	void FillRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned angleInDegrees, unsigned originX, unsigned originY);
	void DrawSurfaceRotated(Int2 dstOffset, const CSurface* pSrc, int angleInDegrees, Int2 origin);
	void DrawSurfaceRotatedCenter(Int2 dstOffset, const CSurface* pSrc, int rotationDegree);
	void DrawSurfaceRotatedCenterAA(Int2 dstOffset, const CSurface* pSrc, int rotationDegree);
	void DrawCircle(int x, int y, int radius, ColorT color);

	ColorT BilinearSample(Int2 xy) const;

	
};
