#pragma once

#include "Image.h"

class Cat : public Image
{
private:
	int bmpMaxWidth{};
	int bmpMaxHeight{};

	int spriteWidth = 32;
	int spriteHeight = 32;

	int orgHeight{};
	int squeezeHeight{};
public:
	bool isJumping = false;
	bool isCollide = false;

	POINT dir{};
	int speed = 4;

	void initialize();
	void move(Direction d);
	void animate();

	void changeSpeed(float mult)
	{
		speed += mult;
	}

	void squeeze() { height = squeezeHeight; dPos.y = squeezeHeight; }
	void original() { height = orgHeight; dPos.y = 0; }
};

inline Cat cat;

void JumpTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);