#pragma once

#include <vector>
#include "Shape.h"

class Board
{
private:
	std::vector<std::vector<Shape>> field;
	std::vector<std::vector<POINT>> pos;
	std::vector<Shape> cells;

	std::vector<POINT> snake; // [0]=PLAYER(머리), 1..=CHASER(꼬리)

	std::vector<POINT> obstacleLoc;
	bool isHigh = false;

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
	int checkObstacleNum();

	TileType getTileType(POINT pos) { return field[pos.x][pos.y].getTileType(); }
	Shape& getTile(POINT pos) { return field[pos.x][pos.y]; }

	POINT findPlayer();
	void processMove();
	void moverMove();

	void applySnakeTiles();
	void swapSnake();
	void explodeSnake();
	void seperateSnake(POINT pos);

	void createItem(TileType type = TileType::MOVER, int x = -1, int y = -1, int r = 255, int g = 0, int b = 0);

	void insertMove3(int x, int y);

	void changeDir(Direction dir);

	// a Key 전용
	void setHighSnake();
	void setNormalSnake();
};

inline Board board;