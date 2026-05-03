#pragma once

#include <vector>
#include "Shape.h"

class Board
{
public:
	void initialize();

	void draw(HDC hDC);

private:
	std::vector<std::vector<Shape>> field;
	std::vector<std::vector<POINT>> pos;

	std::vector<Shape> line;
};
inline Board board;
