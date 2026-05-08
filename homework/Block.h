#pragma once

#include "Image.h"

class Block : public Image
{
public:
	Block();

	void move(Direction dir, int speedMult = 1);

	bool isCollide(POINT& nextPos, Direction dir);

	bool IsMoved() const { return isMoved; }
	bool checkCombine(POINT& nextPos);

private:
	bool isMoved = false;

	int point = 0;
};

inline std::vector<Block> blocks;

