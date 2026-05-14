#include "Cat.h"

void Cat::initialize()
{
	bmpMaxWidth = bmp.bmWidth;
	bmpMaxHeight = bmp.bmHeight;
	bWidth = spriteWidth;
	bHeight = spriteHeight;
}

void Cat::move(int speedMult)
{
	if (ratDraw)
	{
		pos.x += (ws.mousePos.x - pos.x) * 0.05f * speedMult;
		pos.y += (ws.mousePos.y - pos.y) * 0.05f * speedMult;
	}
	else
	{
		dir.x = uid(gen) % 5 - 1;
		dir.y = uid(gen) % 5 - 1;

		pos.x += dir.x * speedMult;
		pos.y += dir.y * speedMult;
	}

	if (pos.x > ws.width) pos.x = 0;
	else if (pos.x < 0) pos.x = ws.width;

	if (pos.y > ws.height) pos.y = 0;
	else if (pos.y < 0) pos.y = ws.height;
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
