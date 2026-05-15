#pragma once

#include <Windows.h>
#include "global.h"
#include "resource.h"

struct Image
{
	HBITMAP bitmap = NULL;
	BITMAP bmp;
	int bWidth{}, bHeight{};
	int rad = 50;

	POINT bPos{};
	POINT pos{};
	POINT dir{ 0,0 }; // 이동할 방향

	COLORREF targetColor{};
	COLORREF tintColor{};

	void load(int idx);
	void draw(HDC hDC, HDC mDC);

	static void ReleaseCachedBitmaps();
};