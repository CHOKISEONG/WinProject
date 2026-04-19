#pragma once

#include "global.h"
#include "Shape.h"

class Road
{
private:
	Shape bkGround; // 배경
	std::vector<Shape> lines;	// 차선
	std::vector<Shape> crossing; // 횡단보도

	// 횡단보도 영역 측정용
	RECT leftCrossing;
	RECT rightCrossing;
	RECT upCrossing;
	RECT downCrossing;
	RECT center;
	std::map<Direction, bool> canCross{};

public:
	void draw(HDC hDC) const;

	void initialize();

	RECT getLeftC() const { return leftCrossing; }
	RECT getRightC() const { return rightCrossing; }
	RECT getUpC() const { return upCrossing; }
	RECT getDown() const { return downCrossing; }
	RECT getCenter() const { return center; }

	std::map<Direction, bool>& checkCross();
};

inline Road road;