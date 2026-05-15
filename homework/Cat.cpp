#include "Cat.h"

void Cat::initialize()
{
	bmpMaxWidth = bmp.bmWidth;
	bmpMaxHeight = bmp.bmHeight;
	bWidth = spriteWidth;
	bHeight = spriteHeight;

	orgHeight = rad;
	squeezeHeight = rad / 2;
}

void Cat::move(Direction d)
{
	if (d == Direction::LEFTDIR)
	{
		dir = { -1, 0 };
		pos.x -= speed;
	}
	else if (d == Direction::RIGHTDIR)
	{
		dir = { 1, 0 };
		pos.x += speed;
	}
		
}

void Cat::animate()
{
	bPos.x += spriteWidth;

	if (isCollide)
	{
		bPos.y = spriteHeight * 6;
		if (bPos.x >= spriteWidth * 3)
			bPos.x = 0;
	}
	else if (isJumping)
	{
		bPos.y = spriteHeight * 8;
		if (bPos.x >= spriteWidth * 7)
			bPos.x = 0;
	}
	else
	{
		bPos.y = spriteHeight * 4;
		if (bPos.x >= bmpMaxWidth)
			bPos.x = 0;
	}
}

void JumpTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static float jumpT = 0.0f;
	jumpT += 1.0f;

	if (jumpT < 20.0f)
	{
		if (cat.dir.y == 0)
		{
			cat.pos.y -= 8;
		}
		else
			cat.pos.x -= 8;
	}
	else if (jumpT < 30.0f)
	{
		if (cat.dir.y == 0)
		{
			cat.pos.y += 16;
		}
		else
			cat.pos.x += 16;
	}
	else
	{
		jumpT = 0.0f;
		cat.isJumping = false;
		cat.pos.y = ws.height * 4 / 5;
		KillTimer(hWnd, 3);
	}
}