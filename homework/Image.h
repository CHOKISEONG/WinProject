#pragma once

#include <Windows.h>
#include "global.h"
#include "resource.h"
#include "Enum.h"

struct Image
{
	HBITMAP bitmap = NULL;
	BITMAP bmp;
	// 비트맵의 가로/세로 크기
	int bWidth{}, bHeight{};

	// 그릴 사각형 가로/세로
	int drawWidth{}, drawHeight{};

	POINT pos{};
	POINT dPos{};

	void setPos(POINT p) { pos = p; }
	void setSize(POINT sz) { drawWidth = sz.x; drawHeight = sz.y; }

	void load(NameEnum name);
	void draw(HDC hDC, HDC mDC);
	void draw(HDC hDC, HDC mDC, POINT sz);

	static void ReleaseCachedBitmaps();
};