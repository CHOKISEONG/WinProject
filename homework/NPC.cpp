#include "NPC.h"

void NPC::draw(HDC hDC) const
{
	for (const auto& b : body)
	{
		b.draw(hDC, curPos);
	}
}

void NPC::move(std::map<Direction, bool>& m)
{
	if (targetPos == point[0])
	{
		if (dir == Direction::RIGHTDIR)
		{
			if (!m[Direction::UPDIR]) return;
		}
		else if (dir == Direction::UPDIR)
		{
			if (!m[Direction::RIGHTDIR]) return;
		}
	}
	else if (targetPos == point[1])
	{
		if (dir == Direction::LEFTDIR)
		{
			if (!m[Direction::UPDIR]) return;
		}
		else if (dir == Direction::UPDIR)
		{
			if (!m[Direction::LEFTDIR]) return;
		}
	}
	else if (targetPos == point[2])
	{
		if (dir == Direction::DOWNDIR)
		{
			if (!m[Direction::LEFTDIR]) return;
		}
		else if (dir == Direction::LEFTDIR)
		{
			if (!m[Direction::DOWNDIR]) return;
		}
	}
	else if (targetPos == point[3])
	{
		if (dir == Direction::RIGHTDIR)
		{
			if (!m[Direction::DOWNDIR]) return;
		}
		else if (dir == Direction::DOWNDIR)
		{
			if (!m[Direction::RIGHTDIR]) return;
		}
	}

	if (curPos != targetPos)
	{
		progress += 0.1f;

		POINT distance = targetPos - curPos;

		curPos.x += distance.x * progress;
		curPos.y += distance.y * progress;
	}
	else
	{
		curPos = targetPos;
		progress = 0.0f;
	}
}

void NPC::OnNotify(TrafficSignal signal)
{
	if (signal == TrafficSignal::RED)
	{
		if (curPos == point[0])
		{
			targetPos = point[3];
			dir = Direction::DOWNDIR;
		}
		else if (curPos == point[1])
		{
			targetPos = point[2];
			dir = Direction::DOWNDIR;
		}
		else if (curPos == point[2])
		{
			targetPos = point[1];
			dir = Direction::UPDIR;
		}
		else if (curPos == point[3])
		{
			targetPos = point[0];
			dir = Direction::UPDIR;
		}
	}
	else if (signal == TrafficSignal::GREEN)
	{
		if (curPos == point[0])
		{
			targetPos = point[1];
			dir = Direction::LEFTDIR;
		}
		else if (curPos == point[1])
		{
			targetPos = point[0];
			dir = Direction::RIGHTDIR;
		}
		else if (curPos == point[2])
		{
			targetPos = point[3];
			dir = Direction::RIGHTDIR;
		}
		else if (curPos == point[3])
		{
			targetPos = point[2];
			dir = Direction::LEFTDIR;
		}
	}
	else if (signal == TrafficSignal::RED_ALL)
	{

	}
}

void NPC::initialize()
{
	body.clear();

	for (int i{}; i < 4; ++ i)
		body.push_back(Shape());

	body[0].setShape(Type::CIRCLE, 20);
	body[0].setColorBrush(RGB(200, 100, 0));

	body[1].setShape(Type::LINE);
	body[1].addPoint(POINT{ -10,-2 });
	body[1].addPoint(POINT{ -2,-2 });

	body[2].setShape(Type::LINE);
	body[2].addPoint(POINT{ 2,-2 });
	body[2].addPoint(POINT{ 10,-2 });

	body[3].setShape(Type::LINE);
	body[3].addPoint(POINT{ -10,5 });
	body[3].addPoint(POINT{ 10,5 });

	int cellW{ ws.WIDTH / 12 };
	int cellH{ ws.HEIGHT / 12 };

	point[0] = POINT{ ws.WIDTH - (int)(cellW * 3.5), (int)(cellH * 3.5) };
	point[1] = POINT{ (int)(cellW * 3.5), (int)(cellH * 3.5) };
	point[2] = POINT{ (int)(cellW * 3.5), ws.HEIGHT - (int)(cellH * 3.5) };
	point[3] = POINT{ ws.WIDTH - (int)(cellW * 3.5), ws.HEIGHT - (int)(cellH * 3.5) };

	curPos = point[0];
	targetPos = curPos;
}


