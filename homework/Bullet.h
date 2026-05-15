#pragma once

#include "Shape.h"

class Bullet : public Shape
{
public:
	POINT pos{};
	POINT dir{};
	int speed = 5;

	Bullet(POINT _pos, POINT _dir, int _speed = 5)
	{
		pos = _pos;
		dir = _dir;
		speed = _speed;
		setShape(Type::CIRCLE, 5);
		setColorBrush(RGB(255, 0, 0));
	}

	void move()
	{
		pos.x += dir.x * speed;
		pos.y += dir.y * speed;

		
	}

	void draw(HDC hDC) const
	{
		Shape::draw(hDC, pos);
	}
};
inline std::vector<Bullet> bullets;

void eraseBullet();
void checkBullet();