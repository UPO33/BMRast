#pragma once

#include <math.h>
#include <memory>

#include "Utility.h"
#include "Int2.h"


typedef unsigned char uint8;
typedef unsigned short uint16;


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
		memset(GetPixels(), color, GetImageSizeInBytes());
	}
	void FillMandelbortFractal();

	
	template<bool bCheckBound> void SetPixel(int x, int y, ColorT color)
	{
		if(bCheckBound)
		{
			if(x < 0 || x >= mWidth 
				|| y < 0 || y >= mHeight) return;
		}
		*GetPixel(x, y) = color;
	}
	template<bool bCheckBound> void SetPixel(int x, int y, int penSize, ColorT color)
	{
		switch (penSize)
		{
		case 1  : SetPixel<bCheckBound>(x,y, color);
			break;

		case 2  : 
			{
				//P0
				//00

				SetPixel<bCheckBound>(x    , y    , color);
				SetPixel<bCheckBound>(x + 1, y    , color);
				SetPixel<bCheckBound>(x + 1, y + 1, color);
				SetPixel<bCheckBound>(x    , y + 1, color);

			}
			break;

		case  3 : 
			{
				SetPixel<bCheckBound>(x    , y - 1, color);
				SetPixel<bCheckBound>(x - 1, y - 1, color);
				SetPixel<bCheckBound>(x + 1, y - 1, color);

				SetPixel<bCheckBound>(x    , y    , color);
				SetPixel<bCheckBound>(x - 1, y    , color);
				SetPixel<bCheckBound>(x + 1, y    , color);

				SetPixel<bCheckBound>(x    , y + 1, color);
				SetPixel<bCheckBound>(x - 1, y + 1, color);
				SetPixel<bCheckBound>(x + 1, y + 1, color);

			};
			break;
		break;
		default:
			{
				for(int i = -(penSize / 2); i <= penSize / 2; i++)
				{
					for(int j = -(penSize / 2); j <= penSize / 2; j++)
					{
						SetPixel<bCheckBound>(x + i, y + j, color);
					}
				}
				return;

			}
		}
	}


	void DrawHorizontalLine(unsigned x0, unsigned x1, unsigned y, unsigned thickness, ColorT color)
	{
		if (x0 > x1)
		{
			std::swap(x0, x1);
		}

		for (; x0 <= x1; x0++)
		{
			SetPixel<true>(x0, y, thickness, color);
		}
	}
	void DrawVerticalLine(unsigned y0, unsigned y1, unsigned x, unsigned thickness, ColorT color)
	{
		if(y0 > y1)
		{
			std::swap(y0, y1);
		}

		for(; y0 <= y1; y0++)
		{
			SetPixel<true>(x, y0, thickness, color);
		}
	}
	void DrawLineAA(int x1, int y1, int x2, int y2, ColorT color);
	void DrawLine(int x1, int y1, int x2, int y2, unsigned thickness, ColorT color)
	{
		int steep = 0;
		int sx    = ((x2 - x1) > 0) ? 1 : -1;
		int sy    = ((y2 - y1) > 0) ? 1 : -1;
		int dx    = abs(x2 - x1);
		int dy    = abs(y2 - y1);

		if (dy > dx)
		{
			std::swap(x1,y1);
			std::swap(dx,dy);
			std::swap(sx,sy);

			steep = 1;
		}

		int e = 2 * dy - dx;

		for (int i = 0; i < dx; ++i)
		{
			if (steep)
				SetPixel<true>(y1, x1, thickness, color);
			else
				SetPixel<true>(x1, y1, thickness, color);

			while (e >= 0)
			{
				y1 += sy;
				e -= (dx << 1);
			}

			x1 += sx;
			e  += (dy << 1);
		}

		SetPixel<true>(x2,y2, thickness, color);
	}

	
	void BlendRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color);
	void DrawLine(int x0, int y0, int x1, int y1, ColorT color);
	void FillCircle(unsigned x, unsigned y, unsigned radius, ColorT color);
	void FillRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h);
	void DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned angleInDegrees, unsigned originX, unsigned originY);
	void DrawSurfaceRotated(Int2 dstOffset, const CSurface* pSrc, int angleInDegrees, Int2 origin);
	void DrawSurfaceRotatedCenter(Int2 dstOffet, const CSurface* pSrc, int rotationDegree);
};
