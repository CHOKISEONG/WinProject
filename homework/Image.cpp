#include "Image.h"
#include "Board.h"
#include <map>

namespace
{
	std::map<int, HBITMAP> g_bitmapCache;

	HBITMAP GetOrLoadBitmap(int idx)
	{
		auto it = g_bitmapCache.find(idx);
		if (it != g_bitmapCache.end())
			return it->second;

		const int resId = (idx < 0) ? IDB_BITMAPCOL : (IDB_BITMAP1 + idx);
		HBITMAP hbmp = LoadBitmap(ws.instance, MAKEINTRESOURCE(resId));
		g_bitmapCache.insert(std::make_pair(idx, hbmp));
		return hbmp;
	}
}

void Image::load(int idx)
{
	// 여기서 DeleteObject(bitmap) 하면 안 됩니다 (핸들 공유/복사 때문에 다른 객체까지 깨짐)
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

	StretchBlt(
		hDC,
		pos.x - rad, pos.y - rad,
		rad * 2, rad * 2,
		mDC,
		0, 0, bWidth, bHeight,
		SRCCOPY
	);

	SelectObject(mDC, old);
}
