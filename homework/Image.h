#pragma once

#include <Windows.h>
#include "global.h"
#include "resource.h"

struct Image
{
	HBITMAP bitmap = NULL;
	BITMAP bmp;
	int bWidth{}, bHeight{};
	POINT bPos{};
	int rad = 50;

	POINT pos{};

	void load(int idx);
	void draw(HDC hDC, HDC mDC);

	static void ReleaseCachedBitmaps();
};
inline Image background;

inline Image rat;
inline bool ratDraw = false;