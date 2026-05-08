#include "Board.h"
#include "Block.h"
#include <numeric>

void Board::initialize()
{
	pos.resize(boardCol);
	for (int i{}; i < boardCol; ++i)
	{
		pos[i].resize(boardCol);
		for (int y{}; y < boardRow; ++y)
		{
			pos[i][y] = POINT{ i * cell + rad, y * cell + rad };
		}
	}

	line.resize(boardRow + boardCol + 2);
	for (int i{}; i < boardRow; ++i)
	{
		line[i].setShape(Shape::Type::LINE);
		line[i].addPoint(POINT{ 0, (i + 1) * cell });
		line[i].addPoint(POINT{ WIDTH, (i + 1) * cell });
		line[i].setColorBrush(RGB(0,0,0));
		line[i].setColorPen(RGB(0, 0, 0));
	}
	for (int i{ boardRow }; i < boardRow + boardCol; ++i)
	{
		line[i].setShape(Shape::Type::LINE);
		line[i].addPoint(POINT{ (i + 1 - boardRow) * cell, 0 });
		line[i].addPoint(POINT{ (i + 1 - boardRow) * cell, HEIGHT });
		line[i].setColorBrush(RGB(0, 0, 0));
		line[i].setColorPen(RGB(0, 0, 0));
	}
}

void Board::draw(HDC hDC, HDC mDC)
{
	for (auto& c : collide)
	{
		c.draw(hDC, mDC);
	}

	for (auto& l : line)
	{
		l.draw(hDC, POINT{ 0,0 });
	}
}

void Board::makeCollide(int num)
{
	collide.clear();
	collideRect.clear();
	indices.clear();
	indices.resize(boardRow * boardCol);
	std::iota(indices.begin(), indices.end(), 0);
	std::shuffle(indices.begin(), indices.end(), gen);

	for (int i{}; i < num; ++i)
	{
		collide.push_back(Image());
		collide[i].load(-1);

		const int col = indices[i] % boardCol;
		const int row = indices[i] / boardCol;

		collide[i].pos.x = col * cell + rad;
		collide[i].pos.y = row * cell + rad;
		collide[i].rad = rad;

		collideRect.push_back(RECT{ collide[i].pos.x - rad,collide[i].pos.y - rad,collide[i].pos.x + rad,collide[i].pos.y + rad });
	}

	indices.erase(indices.begin(), indices.begin() + num);

	blocks.clear();
	for (int i{}; i < num; ++i)
		blocks.push_back(Block());
}

POINT Board::getRandPos()
{
	std::vector<POINT> makablePoint;
	for (const auto& ps : indices)
	{
		POINT p = POINT{ ps % boardCol, ps / boardCol };

		bool canMake = true;
		for (int i{}; i < blocks.size(); ++i)
		{
			RECT targetRect{ blocks[i].pos.x - rad, blocks[i].pos.y - rad, blocks[i].pos.x + rad, blocks[i].pos.y + rad };
			
			if (PtInRect(&targetRect, pos[p.x][p.y]))
				canMake = false;
		}

		if (canMake)
			makablePoint.push_back(pos[p.x][p.y]);
	}

	if (makablePoint.size() < 2)
		return POINT{ -1,-1 };
	else
		return makablePoint[uid(gen) % makablePoint.size()];
}
