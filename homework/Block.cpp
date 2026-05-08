#include "Block.h"
#include "Board.h"
#include <cstdlib> // abs

Block::Block()
{
	load(0);
	pos = board.getRandPos();
}

void Block::draw(HDC hDC, HDC mDC)
{
	if (!isAlive) return;
	Image::draw(hDC, mDC);
}

void Block::move(Direction dir, int speedMult)
{
	if (!isAlive)
	{
		isMoved = false;
		return;
	}

	const int speed = 6 * speedMult;

	int dx = 0, dy = 0;
	switch (dir)
	{
	case Direction::LEFTDIR:  dx = -speed; break;
	case Direction::RIGHTDIR: dx = speed; break;
	case Direction::UPDIR:    dy = -speed; break;
	case Direction::DOWNDIR:  dy = speed; break;
	default: break;
	}

	const int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
	const int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
	const int steps = std::abs(dx) + std::abs(dy);

	bool movedAny = false;

	for (int i = 0; i < steps; ++i)
	{
		POINT candidate = pos;
		candidate.x += stepX;
		candidate.y += stepY;

		if (isCollide(candidate, dir))
			break;

		if (checkCombine(candidate))
		{
			isMoved = true;
			return;
		}

		pos = candidate;
		movedAny = true;
	}

	isMoved = movedAny;
}

bool Block::isCollide(POINT& nextPos, Direction dir)
{
	RECT myRect{ nextPos.x - rad, nextPos.y - rad, nextPos.x + rad, nextPos.y + rad };
	RECT destRect{};

	// 장애물과의 충돌
	const auto& collide = board.getCollideRect();
	for (int i = 0; i < (int)collide.size(); ++i)
	{
		if (IntersectRect(&destRect, &collide[i], &myRect))
			return true;
	}

	// 벽과의 충돌
	for (const auto& rt : ws.outOfWindowRect)
	{
		if (IntersectRect(&destRect, &rt, &myRect))
			return true;
	}

	// 다른 블록과의 충돌
	for (int i = 0; i < (int)blocks.size(); ++i)
	{
		if (!blocks[i].isAlive) continue;
		if (&blocks[i] == this) continue;
		if (blocks[i].point == point) continue;

		RECT targetRect{ blocks[i].pos.x - rad, blocks[i].pos.y - rad, blocks[i].pos.x + rad, blocks[i].pos.y + rad };

		if (IntersectRect(&destRect, &myRect, &targetRect))
			return true;
	}

	return false;
}

bool Block::checkCombine(POINT& nextPos)
{
	for (int i = 0; i < (int)blocks.size(); ++i)
	{
		if (!blocks[i].isAlive) continue;
		if (&blocks[i] == this) continue;
		if (blocks[i].point != point) continue;

       RECT otherRect{ blocks[i].pos.x - rad, blocks[i].pos.y - rad, blocks[i].pos.x + rad, blocks[i].pos.y + rad };
		RECT myNextRect{ nextPos.x - rad, nextPos.y - rad, nextPos.x + rad, nextPos.y + rad };
		RECT dest{};
		if (IntersectRect(&dest, &otherRect, &myNextRect))
		{
			const POINT combinedCenter = blocks[i].pos;
			blocks[i].isAlive = false;

			point += 1;
			if (point > highestPoint)
				highestPoint = point;
			isMoved = true;

			pos = combinedCenter;
			load(point);
			return true;
		}
	}
	return false;
}
