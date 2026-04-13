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
	bool isObstacle(POINT p) const;
	bool isSnakeAt(POINT p) const;
	POINT nextPos(POINT from, Direction dir) const;

	void clearSnakeTiles();
	

public:
	Board();
	void initialize();

	Direction getDir() { return field[snake[0].x][snake[0].y].getDir(); }

	void draw(HDC hDC) const;

	bool checkCollide(POINT from, POINT to);

	POINT findPlayer();
	void processMove();
	void moverMove();
	void applySnakeTiles();
	void swapSnake();

	void createItem(TileType type = TileType::MOVER, int x = -1, int y = -1);

	void changeDir(Direction dir);
};

inline Board board;