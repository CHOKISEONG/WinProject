#pragma once

#include "header.h"

enum Type
{
	NONE,
	RECT,
	CIRCLE,
	TRIANGLE
};

class Shape
{
private:
	POINT pos = POINT{ 0,0 };

	Type type;

	float moveSpeed = 1.0f;
	POINT moveDir = POINT{ 0,0 };

public:
	bool isDrawing = false;
	bool isMoving = false;

	Shape()
		:type(Type::NONE)
	{
	}
	Shape(Type drawType)
		:type(drawType)
	{
	}

	void draw(HDC hDC) const;

	void setPos(POINT _pos) { pos = _pos; }
	void setType(Type _type) { type = _type; }
	void setDir(float degree);

	POINT getPos() const { return pos; }

	void changeSpeed(float delta) { moveSpeed += delta; }
};

inline Shape shape;