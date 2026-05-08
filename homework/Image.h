#pragma once

#include <Windows.h>
#include "global.h"
#include "resource.h"

struct Image
{
	HBITMAP bitmap = NULL;
	BITMAP bmp;
	int bWidth{}, bHeight{};

	POINT pos{};
	POINT dir{ 0,0 }; // 이동할 방향

	void load(int idx);
	void draw(HDC hDC, HDC mDC);

	static void ReleaseCachedBitmaps();
};