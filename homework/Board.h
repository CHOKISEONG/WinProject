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
	void makeItem(int num);
	POINT getRandPos();

	int targetPoint{4};
	bool isGameStarted = false;

	std::vector<RECT>& getCollideRect() { return collideRect; }
	std::vector<std::vector<POINT>>& getPos() { return pos; }

private:
	std::vector<std::vector<POINT>> pos;

	std::vector<Shape> collide;
	std::vector<POINT> collidePos;
	std::vector<RECT> collideRect;

	std::vector<Shape> items;
	std::vector<POINT> itemPos;

	std::vector<int> indices;
};
inline Board board;
