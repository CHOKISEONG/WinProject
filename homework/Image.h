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
	int width{ 50 }, height{ 50 };

	POINT pos{};
	POINT dPos{};

	void load(int idx);
	void draw(HDC hDC, HDC mDC);

	static void ReleaseCachedBitmaps();
};
inline Image background[4];

inline Image rat;
inline bool ratDraw = false;