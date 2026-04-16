#include "Car.h"

void Car::draw(HDC hDC) const
{
	body.draw(hDC, pos);
}

void Car::initialize()
{
	body.clearAll();
	body.setShape(Type::POLYGON);
	body.setColorBrush(RGB(255, 244, 79));

	radius = (ws.WIDTH > ws.HEIGHT) ? ws.HEIGHT / 40 : ws.WIDTH / 40;

	body.addPoint(POINT{ -radius, -radius / 2 });
	body.addPoint(POINT{ radius, -radius / 2 });
	body.addPoint(POINT{ radius, radius / 2 });
	body.addPoint(POINT{ -radius, radius / 2 });
}

bool Car::isInside(POINT p)
{
	return false;
}

void Car::move()
{
	float delta = 5.0f * deltaTime;
	if (dir != Direction::STOP)
	{
		speed += delta;
	}
	else
	{
		speed *= 0.9f;
	}

	switch (dir)
	{
	case Direction::LEFTDIR:
		pos.x -= speed;
		break;
	case Direction::RIGHTDIR:
		pos.x += speed;
		break;
	case Direction::UPDIR:
		pos.y -= speed;
		break;
	case Direction::DOWNDIR:
		pos.y += speed;
		break;
	default:
		break;
	}
}
