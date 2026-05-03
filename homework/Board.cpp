#include "Board.h"

void Board::initialize()
{
	
	field.resize(boardCol);
	pos.resize(boardCol);
	for (int i{}; i < boardCol; ++i)
	{
		field[i].resize(boardCol);
		pos[i].resize(boardCol);
		for (int y{}; y < boardRow; ++y)
		{
			field[i][y].setShape(Shape::Type::RECTANGLE, rad);
			pos[i][y] = POINT{ i * cell + rad, y * cell + rad };
		}
	}

	line.resize(boardRow + boardCol + 2);
	for (int i{}; i < boardRow; ++i)
	{
		line[i].setShape(Shape::Type::LINE);
		line[i].addPoint(POINT{ 0, (i + 1) * cell });
		line[i].addPoint(POINT{ WIDTH, (i + 1) * cell });
		line[i].setColorBrush(RGB(255,255,255));
		line[i].setColorPen(RGB(255, 255, 255));
	}
	for (int i{ boardRow }; i < boardRow + boardCol; ++i)
	{
		line[i].setShape(Shape::Type::LINE);
		line[i].addPoint(POINT{ (i + 1 - boardRow) * cell, 0 });
		line[i].addPoint(POINT{ (i + 1 - boardRow) * cell, HEIGHT });
		line[i].setColorBrush(RGB(255, 255, 255));
		line[i].setColorPen(RGB(255, 255, 255));
	}
}

void Board::draw(HDC hDC)
{
	for (auto& l : line)
	{
		l.draw(hDC, POINT{ 0,0 });
	}

	for (int i{}; i < field.size(); ++i)
	{
		for (int j{}; j < field[i].size(); ++j)
		{
			field[i][j].draw(hDC, pos[i][j]);
		}
	}
}
