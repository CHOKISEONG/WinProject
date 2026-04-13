#pragma once

#include <vector>
#include "Shape.h"

class Board
{
private:
	std::vector<std::vector<Shape>> field;
	std::vector<std::vector<POINT>> pos;
	std::vector<Shape> cells;

	std::vector<POINT> snake; // [0]=PLAYER(¸Ó¸®), 1..=CHASER(²¿¸®)

	bool isInside(POINT p) const;
	bool isSnakeAt(POINT p) const;
	POINT nextPos(POINT from, Direction dir) const;

	void clearSnakeTiles();
	

public:
	Board();
	void initialize();

	void draw(HDC hDC) const;

	POINT findPlayer();
	void processMove();
	void applySnakeTiles();

	void createItem();

	void changeDir(Direction dir);
};

inline Board board;