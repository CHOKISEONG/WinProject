#include "Cat.h"

void Cat::initialize()
{
	bmpMaxWidth = bmp.bmWidth;
	bmpMaxHeight = bmp.bmHeight;
	bWidth = spriteWidth;
	bHeight = spriteHeight;
}

void Cat::moves()
{
	if (ratDraw)
	{
		pos.x += (ws.mousePos.x - pos.x) * 0.05f * speed;
		pos.y += (ws.mousePos.y - pos.y) * 0.05f * speed;
	}
	else
	{
		dir.x = uid(gen) % 5 - 1;
		dir.y = uid(gen) % 5 - 1;

		pos.x += dir.x * speed;
		pos.y += dir.y * speed;
	}

	if (pos.x > ws.width) pos.x = 0;
	else if (pos.x < 0) pos.x = ws.width;

	if (pos.y > ws.height) pos.y = 0;
	else if (pos.y < 0) pos.y = ws.height;
}

void Cat::move(int speedMult, POINT p)
{
	pos.x += (p.x - pos.x) * 0.05f * speedMult * speed;
	pos.y += (p.y - pos.y) * 0.05f * speedMult * speed;
}

void Cat::animate()
{
	bPos.x += spriteWidth;

	if (ratDraw)
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
