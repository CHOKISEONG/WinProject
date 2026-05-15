#pragma once

#include "Image.h"

class Pacman : public Image
{
public:
	POINT dir;
	float speed = 1.0f;

	float animT{};

	bool otherAnim = false;

	void initialize();

	void move();

	void animation();

	void setDir(POINT _dir) { dir = _dir; }

	RECT getRect() const
	{
		int r = rad - 3;
		return RECT{ pos.x - r, pos.y - r, pos.x + r, pos.y + r };
	}
	
	void setBPos(POINT _bPos) { bPos = _bPos; }
};
inline Pacman player;

void OtherAnimTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);