#pragma comment(lib, "msimg32.lib")

#include "Image.h"
#include <map>

namespace
{
	std::map<NameEnum, HBITMAP> g_bitmapCache;

	HBITMAP GetOrLoadBitmap(NameEnum name)
	{
		auto it = g_bitmapCache.find(name);
		if (it != g_bitmapCache.end())
			return it->second;

		HANDLE hImage = LoadImage(
			ws.instance,
			MAKEINTRESOURCE(IDB_BITMAP1 + static_cast<int>(name)),
			IMAGE_BITMAP,                   
			0, 0,                           
			LR_DEFAULTCOLOR | LR_CREATEDIBSECTION
		);

		HBITMAP hbmp = static_cast<HBITMAP>(hImage);
		g_bitmapCache[name] = hbmp;

		return hbmp;
	}
}
void Image::load(NameEnum name)
{
	bitmap = GetOrLoadBitmap(name);

	if (bitmap == NULL)
	{
		ZeroMemory(&bmp, sizeof(bmp));
		bWidth = bHeight = 0;
		return;
	}

	GetObject(bitmap, sizeof(BITMAP), &bmp);
	drawWidth = bWidth = bmp.bmWidth;
	drawHeight = bHeight = bmp.bmHeight;
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
		pos.x - drawWidth/2, pos.y - drawHeight/2,
		drawWidth, drawHeight,
		mDC,
		0, 0, bWidth, bHeight,
		SRCCOPY
	);*/

	TransparentBlt(
		hDC,
		pos.x + dPos.x - drawWidth / 2, pos.y + dPos.y - drawHeight / 2,
		drawWidth, drawHeight,
		mDC,
		0, 0, bWidth, bHeight,
		RGB(255,255,255)
	);

	SelectObject(mDC, old);
}

void Image::draw(HDC hDC, HDC mDC, POINT sz)
{
	drawWidth = sz.x;
	drawHeight = sz.y;
	draw(hDC, mDC);
}
