#pragma once

#include <vector>
#include "Shape.h"
#include "Image.h"

class Board
{
public:
	void initialize();

	void draw(HDC hDC, HDC mDC);

	void makeCollide(int num);
	POINT getRandPos();

	int targetPoint{32};
	bool isGameStarted = false;

	std::vector<RECT>& getCollideRect() { return collideRect; }

private:
	std::vector<std::vector<POINT>> pos;

	std::vector<Image> collide;
	std::vector<RECT> collideRect;

	std::vector<Shape> line;

	std::vector<int> indices;
};
inline Board board;
