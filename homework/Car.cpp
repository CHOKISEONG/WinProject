#include "Car.h"
#include "Road.h"

void Car::draw(HDC hDC) const
{
	body.draw(hDC, pos);

	if (pos.x < radius)
	{
		POINT wrapPos = { pos.x + ws.WIDTH, pos.y };
		body.draw(hDC, wrapPos);
	}
	else if (pos.x > ws.WIDTH - radius)
	{
		POINT wrapPos = { pos.x - ws.WIDTH, pos.y };
		body.draw(hDC, wrapPos);
	}

	if (pos.y < radius)
	{
		POINT wrapPos = { pos.x, pos.y + ws.HEIGHT };
		body.draw(hDC, wrapPos);
	}
	else if (pos.y > ws.HEIGHT - radius)
	{
		POINT wrapPos = { pos.x, pos.y - ws.HEIGHT };
		body.draw(hDC, wrapPos);
	}
}

void Car::OnNotify(TrafficSignal signal)
{
	if (signal == TrafficSignal::RED)
	{
		if (dir == Direction::LEFTDIR || dir == Direction::RIGHTDIR)
		{
			checkCrossing = true;
			isMoving = false;
		}
		else
		{
			checkCrossing = false;
			isMoving = true;
		}
			
	}
	else if (signal == TrafficSignal::GREEN)
	{
		if (dir == Direction::LEFTDIR || dir == Direction::RIGHTDIR)
		{
			checkCrossing = false;
			isMoving = true;
		}
		else
		{
			checkCrossing = true;
			isMoving = false;
		}
	}
	else if (signal == TrafficSignal::RED_ALL)
	{
		checkCrossing = true;
		isMoving = false;
	}
}

void Car::initialize(Direction d)
{
	body.clearAll();
	body.setShape(Type::POLYGON);
	body.setColorBrush(RGB(255, 244, 79));

	dir = d;

	radius = (ws.WIDTH > ws.HEIGHT) ? ws.HEIGHT / 30 : ws.WIDTH / 30;

	if (d == Direction::UPDIR || d == Direction::DOWNDIR)
	{
		body.addPoint(POINT{ -radius / 2, -radius });
		body.addPoint(POINT{ radius / 2, -radius });
		body.addPoint(POINT{ radius / 2, radius });
		body.addPoint(POINT{ -radius / 2, radius });

		collider.left = -radius / 2;
		collider.right = radius / 2;
		collider.top = -radius;
		collider.bottom = radius;
	}
	else
	{
		body.addPoint(POINT{ -radius, -radius / 2 });
		body.addPoint(POINT{ radius, -radius / 2 });
		body.addPoint(POINT{ radius, radius / 2 });
		body.addPoint(POINT{ -radius, radius / 2 });

		collider.top = -radius / 2;
		collider.bottom = radius / 2;
		collider.left = -radius;
		collider.right = radius;
	}
}

RECT Car::getRect() const
{
	RECT r = collider;
	r.left += pos.x;
	r.right += pos.x;
	r.top += pos.y;
	r.bottom += pos.y;
	return r;
}

void Car::setPos(POINT p)
{
	pos = p;

	if (dir == Direction::LEFTDIR)
	{
		dPos.push_back(POINT{ -radius * 2, 0 });
		dPos.push_back(POINT{ -radius * 2, radius });
		dPos.push_back(POINT{ -radius * 2, -radius });
	}
	else if (dir == Direction::RIGHTDIR)
	{
		dPos.push_back(POINT{ radius * 2, 0 });
		dPos.push_back(POINT{ radius * 2, radius });
		dPos.push_back(POINT{ radius * 2, -radius });
	}
	else if (dir == Direction::UPDIR)
	{
		dPos.push_back(POINT{ 0, -radius * 2});
		dPos.push_back(POINT{ radius, -radius * 2 });
		dPos.push_back(POINT{ -radius, -radius * 2 });
	}
	else if (dir == Direction::DOWNDIR)
	{
		dPos.push_back(POINT{ 0, radius * 2});	
		dPos.push_back(POINT{ radius, radius * 2 });
		dPos.push_back(POINT{ radius, radius * 2 });
	}
}

bool Car::isInside(POINT p)
{
	return false;
}

bool Car::isCollide(POINT p)
{
	if (getDistance(pos, p) <= radius) return true;
	return false;
}

void Car::checkCollide()
{
	for (const auto& d : dPos)
	{
		POINT myFront = pos;
		myFront.x += d.x;
		myFront.y += d.y;

		for (const auto& c : cars)
		{
			if (c.get() == this) continue;

			if (c->isCollide(myFront))
			{
				speed = 0.0f;
				isMoving = false;
				return;
			}
			else
			{
				isMoving = true;
			}
		}
	}
}

void Car::checkSignal()
{
	if (!checkCrossing) return;

	RECT r = road.getCenter();
	POINT p = POINT{ pos.x + dPos[0].x, pos.y + dPos[0].y };
	if (PtInRect(&r, p))
	{
		speed = 0.0f;
		isMoving = false;
	}
}

void Car::move()
{
	float delta = dSpeed * deltaTime;
	if (isMoving && speed <= 10.0f)
	{
		speed += delta;
	}
	else
	{
		speed *= 0.9f;
	}
	
	float d = speed;
	bool isReversing = false;
	if (checkCrossing && IsColliding(getRect(), road.getCenter()))
	{
		d = reverseSpeed;
		isReversing = true;
	}

	POINT oldPos = pos;

	// 움직이기
	switch (dir)
	{
	case Direction::LEFTDIR:
		pos.x -= d;
		if (pos.x + radius <= 0) pos.x += ws.WIDTH;
		else if (pos.x - radius >= ws.WIDTH) pos.x -= ws.WIDTH;
		break;
	case Direction::RIGHTDIR:
		pos.x += d;
		if (pos.x + radius <= 0) pos.x += ws.WIDTH;
		else if (pos.x - radius >= ws.WIDTH) pos.x -= ws.WIDTH;
		break;
	case Direction::UPDIR:
		pos.y -= d;
		if (pos.y + radius <= 0) pos.y += ws.HEIGHT;
		else if (pos.y - radius >= ws.HEIGHT) pos.y -= ws.HEIGHT;
		break;
	case Direction::DOWNDIR:
		pos.y += d;
		if (pos.y + radius <= 0) pos.y += ws.HEIGHT;
		else if (pos.y - radius >= ws.HEIGHT) pos.y -= ws.HEIGHT;
		break;
	default:
		break;
	}

	// 다른차 밀어내기
	float pushAmount = std::abs(d * 2);
	for (const auto& otherCar : cars)
	{
		if (otherCar.get() == this) continue;

		if (IsColliding(this->getRect(), otherCar->getRect()))
		{
			switch (dir)
			{
			case Direction::LEFTDIR:
				otherCar->pos.x += pushAmount;
				break;
			case Direction::RIGHTDIR:
				otherCar->pos.x -= pushAmount;
				break;
			case Direction::UPDIR:
				otherCar->pos.y += pushAmount;
				break;
			case Direction::DOWNDIR:
				otherCar->pos.y -= pushAmount;
				break;
			}
		}
	}
}
