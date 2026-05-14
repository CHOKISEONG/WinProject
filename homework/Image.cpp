#pragma comment(lib, "msimg32.lib")

#include "Image.h"
#include <map>

namespace
{
	std::map<int, HBITMAP> g_bitmapCache;

	HBITMAP GetOrLoadBitmap(int idx)
	{
		auto it = g_bitmapCache.find(idx);
		if (it != g_bitmapCache.end())
			return it->second;

		HBITMAP hbmp = LoadBitmap(ws.instance, MAKEINTRESOURCE(IDB_BITMAP1 + idx));
		g_bitmapCache.insert(std::make_pair(idx, hbmp));
		return hbmp;
	}
}

void Image::load(int idx)
{
	bitmap = GetOrLoadBitmap(idx);

	if (bitmap == NULL)
	{
		ZeroMemory(&bmp, sizeof(bmp));
		bWidth = bHeight = 0;
		return;
	}

	GetObject(bitmap, sizeof(BITMAP), &bmp);
	bWidth = bmp.bmWidth;
	bHeight = bmp.bmHeight;
}

void Image::ReleaseCachedBitmaps()
{
	for (auto it = g_bitmapCache.begin(); it != g_bitmapCache.end(); ++it)
	{
		if (it->second != NULL)
			DeleteObject(it->second);
	}
	g_bitmapCache.clear();
}

void Image::draw(HDC hDC, HDC mDC)
{
	if (bitmap == NULL) return;

	HBITMAP old = (HBITMAP)SelectObject(mDC, bitmap);

	/*StretchBlt(
		hDC,
		pos.x - rad, pos.y - rad,
		rad * 2, rad * 2,
		mDC,
		bPos.x, bPos.y, bWidth, bHeight,
		SRCCOPY
	);*/

	TransparentBlt(
		hDC,
		pos.x - rad, pos.y - rad,
		rad * 2, rad * 2,
		mDC,
		bPos.x, bPos.y, bWidth, bHeight,
		RGB(255, 255, 255)
	);

	SelectObject(mDC, old);
}
