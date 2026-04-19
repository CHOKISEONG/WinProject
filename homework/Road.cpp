#include "Road.h"
#include "Car.h"

void Road::draw(HDC hDC) const
{
	bkGround.draw(hDC);

	for (const auto& c : crossing)
	{
		c.draw(hDC);
	}

	for (const auto& l : lines)
	{
		l.draw(hDC);
	}
}

void Road::initialize()
{
	bkGround.clearAll();
	bkGround.setColorBrush(RGB(0, 0, 0));
	bkGround.setColorPen(RGB(0, 0, 0));
	bkGround.setType(Type::RECTANGLE);
	bkGround.addPoint(POINT{ 0,0 });
	bkGround.addPoint(POINT{ ws.WIDTH,0 });
	bkGround.addPoint(POINT{ ws.WIDTH,ws.HEIGHT });
	bkGround.addPoint(POINT{ 0,ws.HEIGHT });

	lines.clear();
	crossing.clear();

	int cellH = (int)(ws.HEIGHT * 0.16666f);
	int cellW = (int)(ws.WIDTH * 0.16666f);

	for (int i{}; i < 12; ++i)
	{
		lines.push_back(Shape(Type::LINE));
		lines[i].setColorPen(RGB(255, 255, 255));
	}


	// 가로 도로
	int idx{};
	int w[4]{ 0, cellW * 2, cellW * 4, ws.WIDTH };
	for (int i{}; i < 4; i += 2)
	{
		lines[idx].addPoint(POINT{ w[i], cellH * 2 });
		lines[idx].addPoint(POINT{ w[i + 1], cellH * 2 });
		lines[idx].setThickness(3);

		lines[idx + 1].addPoint(POINT{ w[i], cellH * 3 });
		lines[idx + 1].addPoint(POINT{ w[i + 1], cellH * 3 });
		lines[idx + 1].setPenStyle(PS_DASHDOT);

		lines[idx + 2].addPoint(POINT{ w[i], cellH * 4 });
		lines[idx + 2].addPoint(POINT{ w[i + 1], cellH * 4 });
		lines[idx + 2].setThickness(3);

		idx += 3;
	}

	// 세로 도로
	int h[4]{ 0, cellH * 2, cellH * 4, ws.HEIGHT };
	for (int i{}; i < 4; i += 2)
	{
		lines[idx].addPoint(POINT{ cellW * 2, h[i] });
		lines[idx].addPoint(POINT{ cellW * 2 , h[i + 1] });
		lines[idx].setThickness(3);

		lines[idx + 1].addPoint(POINT{ cellW * 3, h[i] });
		lines[idx + 1].addPoint(POINT{ cellW * 3, h[i + 1] });
		lines[idx + 1].setPenStyle(PS_DASHDOT);

		lines[idx + 2].addPoint(POINT{ cellW * 4, h[i] });
		lines[idx + 2].addPoint(POINT{ cellW * 4, h[i + 1] });
		lines[idx + 2].setThickness(3);

		idx += 3;
	}

	// 횡단보도
	for (int i{}; i < 80; ++i)
	{
		crossing.push_back(Shape(Type::LINE));
	}
	for (int i{}; i < 80; ++i)
	{
		crossing[i].setColorPen(RGB(255, 255, 255));
		crossing[i].setColorBrush(RGB(255, 255, 255));
		crossing[i].setThickness(4);
	}

	leftCrossing.left = cellW * 3 / 2;
	leftCrossing.right = cellW * 2;
	leftCrossing.top = h[1];
	leftCrossing.bottom = h[1] + cellH * 2;

	rightCrossing.left = cellW * 4;
	rightCrossing.right = cellW * 5 - (cellW * 2 / 3);
	rightCrossing.top = h[1];
	rightCrossing.bottom = h[1] + cellH * 2;

	for (int i{}; i < 20; ++i)
	{
		int cellLen = cellH / 10 * i;

		crossing[i].addPoint(POINT{ leftCrossing.left, h[1] + cellLen });
		crossing[i].addPoint(POINT{ leftCrossing.right, h[1] + cellLen });
		crossing[40 + i].addPoint(POINT{ rightCrossing.left , h[1] + cellLen });
		crossing[40 + i].addPoint(POINT{ rightCrossing.right, h[1] + cellLen });
	}

	upCrossing.left = w[1];
	upCrossing.right = w[2];
	upCrossing.top = h[1] - cellH / 2;
	upCrossing.bottom = h[1];

	downCrossing.left = w[1];
	downCrossing.right = w[2];
	downCrossing.top = h[2];
	downCrossing.bottom = h[2] + cellH / 2;

	for (int i{ 20 }; i < 40; ++i)
	{
		int cellLen = cellW / 10 * (i - 20);

		crossing[i].addPoint(POINT{ w[1] + cellLen, upCrossing.top });
		crossing[i].addPoint(POINT{ w[1] + cellLen, upCrossing.bottom });

		crossing[40 + i].addPoint(POINT{ w[1] + cellLen, downCrossing.top });
		crossing[40 + i].addPoint(POINT{ w[1] + cellLen, downCrossing.bottom });
	}

	center.left = leftCrossing.left; 
	center.right = rightCrossing.right;
	center.top = upCrossing.top;
	center.bottom = downCrossing.bottom;
}

std::map<Direction,bool>& Road::checkCross()
{
	canCross[Direction::LEFTDIR] = true;
	canCross[Direction::DOWNDIR] = true;
	canCross[Direction::RIGHTDIR] = true;
	canCross[Direction::UPDIR] = true;
	canCross[Direction::DIAGONALDIR] = true;

	for (const auto& c : cars)
	{
		if (IsColliding(c->getRect(), leftCrossing))
		{
			canCross[Direction::LEFTDIR] = false;
		}
		
		if (IsColliding(c->getRect(), rightCrossing))
		{
			canCross[Direction::RIGHTDIR] = false;
		}
		
		if (IsColliding(c->getRect(), upCrossing))
		{
			canCross[Direction::UPDIR] = false;
		}
		
		if (IsColliding(c->getRect(), downCrossing))
		{
			canCross[Direction::DOWNDIR] = false;
		}

		if (IsColliding(c->getRect(), diagonalCrossing))
		{
			canCross[Direction::DIAGONALDIR] = false;
		}
	}

	return canCross;
}
