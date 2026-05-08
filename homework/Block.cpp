#include "Block.h"
#include "Board.h"

Block::Block()
{
	load(0);
	pos = board.getRandPos();
}

void Block::move(Direction dir, int speedMult)
{
	POINT nextPos = pos;

	const int speed = 6 * speedMult;
	switch (dir)
	{
	case Direction::LEFTDIR:  nextPos.x -= speed; break;
	case Direction::RIGHTDIR: nextPos.x += speed; break;
	case Direction::UPDIR:    nextPos.y -= speed; break;
	case Direction::DOWNDIR:  nextPos.y += speed; break;
	default: break;
	}

	if (isCollide(nextPos, dir))
	{
		isMoved = false;
		return;
	}
	else if (checkCombine(nextPos))
	{
		isMoved = true;
		return;
	}
	else
	{
		pos = nextPos;
		isMoved = true;
	}
}

bool Block::isCollide(POINT& nextPos, Direction dir)
{
	RECT myRect{ nextPos.x - rad, nextPos.y - rad, nextPos.x + rad, nextPos.y + rad };
	RECT destRect{};

	// 장애물과의 충돌 계산
	const auto& collide = board.getCollideRect();
	for (int i = 0; i < (int)collide.size(); ++i)
	{
		if (IntersectRect(&destRect, &collide[i], &myRect))
			return true;
	}

	// 벽과의 충돌 계산
	for (const auto& rt : ws.outOfWindowRect)
	{
		if (IntersectRect(&destRect, &rt, &myRect))
			return true;
	}

	// 다른 블록과의 충돌 계산
	for (int i{}; i < blocks.size(); ++i)
	{
		if (&blocks[i] == this) continue;
		else if (blocks[i].point == point) continue;

		RECT targetRect{ blocks[i].pos.x - rad, blocks[i].pos.y - rad, blocks[i].pos.x + rad, blocks[i].pos.y + rad };

		if (IntersectRect(&destRect, &myRect, &targetRect))
			return true;
	}

	return false;
}

bool Block::checkCombine(POINT& nextPos)
{
	std::vector<int> indices;

	for (int i{}; i < blocks.size(); ++i)
	{
		if (&blocks[i] == this) continue;
		else if (blocks[i].point != point) continue;

		RECT myRect{ blocks[i].pos.x - rad, blocks[i].pos.y - rad, blocks[i].pos.x + rad, blocks[i].pos.y + rad };
		if (PtInRect(&myRect, nextPos))
		{
			blocks.erase(blocks.begin() + i);
			point += 1;
			load(point);
			return true;
		}
	}

	return false;
}
