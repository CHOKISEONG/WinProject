#pragma once

#include <Windows.h>
#include "global.h"
#include "resource.h"

struct Target
{
	POINT pos;
	float sizeRatio = 1.0f;
};

struct Magnifier
{
	enum class ArrangeType
	{
		None,
		Middle,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	POINT p[4]{};
	int width{}, height{};

	int zoomDiff = 0;

	bool activate = false;

	ArrangeType arrangeType;

	void setArrangeType(int x, int y);
	void setArrangeType(ArrangeType type) { arrangeType = type; }

	void setMag(POINT pos);

	void draw(HDC hDC);

	void move(POINT pos)
	{
		for (int i{}; i < 4; ++i)
		{
			p[i].x += pos.x;
			p[i].y += pos.y;
		}
	}

	void arrange(POINT pos);
};

struct Image
{
	HBITMAP bitmap = NULL;
	BITMAP bmp;
	int width{}, height{};

	Magnifier mag; // 돋보기
	bool magAll = false;
	bool hInvert = false;
	bool vInvert = false;

	std::vector<Target> target; // 돋보기 붙여넣는 위치들
	int targetRaster = SRCCOPY;

	bool isMoving = false;
	bool isResizing = false;
	float tResize = 0.0f;
	POINT dir{ 5,5 };

	void push(POINT p, float t = 1.0f);

	void load(int idx);
	
	void draw(HDC hDC, HDC mDC);

	void reset();

	void move();

	void resize();
};
inline Image img;