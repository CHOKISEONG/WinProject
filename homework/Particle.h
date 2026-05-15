#pragma once

#include "Shape.h"

class Particle : public Shape
{
private:
	POINT pos;
	POINT dir;
public:
	Particle(POINT p)
	{
		pos = p;
		setShape(Type::CIRCLE, 10);
		setColorBrush(RGB(uidColor(gen), uidColor(gen), uidColor(gen)));
		dir.x = uid(gen) % 11 - 5;
		dir.y = uid(gen) % 11 - 5;
	}

	void move()
	{
		pos.x += dir.x;
		pos.y += dir.y;
	}

	void draw(HDC hDC) const
	{
		Shape::draw(hDC, pos);
	}

	POINT getPos() const { return pos; }
};
inline std::vector<Particle> particles;