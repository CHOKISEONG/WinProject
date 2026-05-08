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

	return false;
}
