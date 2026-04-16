#pragma once

#include "Shape.h"

class Car
{
private:
	Shape body;
	POINT pos;
	Direction dir;

	float speed = 1.0f;
	int radius = 0.0f;
public:
	
	Direction getDir() const { return dir; }
	void setDir(Direction d) { dir = d; }
	void setPos(POINT p) { pos = p; }
	
	// 완성 필요
	bool isInside(POINT p);

	void initialize();
	void move();

	void draw(HDC hDC) const;

};

inline std::vector<Car> cars;