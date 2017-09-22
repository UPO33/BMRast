#include "stdafx.h"
#include "Surface.h"
#include <algorithm>


void CSurface::DrawLine(int x0, int y0, int x1, int y1, ColorT color)
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

void CSurface::FillRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color)
{
	x = std::min(x, mWidth);
	y = std::min(y, mHeight);

	w = std::min(w, mWidth);
	h = std::min(h, mHeight);

	for (unsigned yy = y; yy < h; yy++)
	{
		for (unsigned xx = x; xx < w; xx++)
		{
			*GetPixel(xx, yy) = color;
		}
	}
}

void CSurface::DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc)
{
	if (pSrc == nullptr || dstX >= mWidth || dstY >= mHeight) return;

	unsigned w = std::min(pSrc->mWidth + dstX, mWidth);
	unsigned h = std::min(pSrc->mHeight + dstY, mHeight);

	for (unsigned y = 0; y < h; y++)
	{
		for (unsigned x = 0; x < w; x++)
		{
			*GetPixel(x + dstX, y + dstY) = *(pSrc->GetPixel(x, y));
		}
	}
}

void CSurface::DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h)
{

	
}
