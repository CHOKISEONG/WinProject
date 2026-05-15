#include "Cat.h"

void Cat::initialize()
{
	bmpMaxWidth = bmp.bmWidth;
	bmpMaxHeight = bmp.bmHeight;
	bWidth = spriteWidth;
	bHeight = spriteHeight;
}

void Cat::move(Direction d)
{
	if (d == Direction::LEFTDIR)
	{
		pos.x -= speed;
	}
	else if (d == Direction::RIGHTDIR)
	{
		pos.x += speed;
	}
		
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
