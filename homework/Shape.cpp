#include "Shape.h"

void Shape::checkCollide()
{
	// 좌우이동중일 때
	if (moveDir.y == std::clamp(moveDir.y, -0.05, 0.05))
	{
		if (pos.x < 0 || pos.x > ws.WIDTH)
		{
			pos.y += (ws.HEIGHT + length * 2) % ws.HEIGHT;
			moveDir.x = moveDir.x * -1;
		}

		if (pos.y > ws.HEIGHT)
		{
			pos.y = 0;
		}
	}
	// 상하이동 중일 때
	else if (moveDir.x == std::clamp(moveDir.x, -0.05, 0.05))
	{
		if (pos.y < 0 || pos.y > ws.HEIGHT)
		{
			pos.x += (ws.WIDTH + length * 2) % ws.WIDTH;
			moveDir.y = moveDir.y * -1;
		}

		if (pos.x > ws.WIDTH)
		{
			pos.x = 0;
		}
	}
	// 대각선 이동중일 때
	else
	{
		if (pos.y < 0 || pos.y > ws.HEIGHT)
		{
			moveDir.y = -1.0 * moveDir.y;
		}

		if (pos.x < 0 || pos.x > ws.WIDTH)
		{
			moveDir.x = -1.0 * moveDir.x;
		}
	}


	// 화면 넘어가지 못하게 용 (나중에 수정 필요0
	if (pos.x < 0)
		pos.x = 50;
	else if (pos.x > ws.WIDTH)
		pos.x = ws.WIDTH - 50;
	else if (pos.y < 0)
	{
		pos.y = 50;
	}
	else if (pos.y > ws.HEIGHT)
	{
		pos.y = ws.HEIGHT - 50;
	}
}

void Shape::draw(HDC hDC)
{
	if (type == Type::NONE || isDrawing == false) return;
	else if (points.size() == 0) return;

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);

	std::vector<POINT> p;
	p.reserve(points.size());
	for (int i{}; i < (int)points.size(); ++i)
	{
		p.push_back(POINT{ points[i].x + (int)pos.x + (int)dPos.x, points[i].y + (int)pos.y + (int)dPos.y });
	}

	switch (this->type)
	{
	case TRIANGLE:case RECTANGLE:
		Polygon(hDC, p.data(), (int)p.size());
		break;
	case CIRCLE:
		Ellipse(hDC, p[0].x, p[0].y, p[1].x, p[1].y);
		break;
	default:
		break;
	}

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

	if (isMoving)
	{
		pos.x += moveDir.x * moveSpeed;
		pos.y += moveDir.y * moveSpeed;
	}
}

void Shape::setDir(float degree)
{
	const double rad = getRadian(degree);
	moveDir.x = cos(rad);
	moveDir.y = sin(rad);

	isMoving = true;
}

void Shape::setShape(Type _type, int _length)
{
	clear();
	type = _type;
	length = _length;

	switch (type)
	{
	case CIRCLE:
		addPoint(POINT{ -_length,-_length });
		addPoint(POINT{ _length,_length });
		break;
	case TRIANGLE:
		for (int i{}; i < 3; ++i)
		{
			int x = _length * cos(getRadian(i * 120.0f));
			int y = _length * sin(getRadian(i * 120.0f));

			addPoint(POINT{ x,y });
		}
		break;
	case RECTANGLE:
		for (int i{}; i < 4; ++i)
		{
			int x = _length * cos(getRadian(i * 90.0f));
			int y = _length * sin(getRadian(i * 90.0f));

			addPoint(POINT{ x,y });
		}
		break;
	default:
		break;
	}
}

void shapeInitialize()
{
	for (int i{}; i < 4; ++i)
	{
		shapes[i].clear();
	}
	shapes.clear();

	shapes.resize(4);
	for (int i{}; i < 4; ++i)
	{
		shapes[i].resize(4);
	}

	for (int i{}; i < 4; ++i)
	{
		shapes[i][0].setShape(Type::CIRCLE, 5);
		shapes[i][1].setShape(Type::CIRCLE, min(ws.WIDTH / 4, ws.HEIGHT / 4));
		shapes[i][2].setShape(Type::CIRCLE, 10);
		shapes[i][3].setShape(Type::RECTANGLE, min(ws.WIDTH / 2, ws.HEIGHT / 2));
	}
	shapes[0][0].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.25 });
	shapes[0][1].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.25 });
	shapes[0][2].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.25 });
	shapes[0][3].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.25 });

	shapes[1][0].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.75 });
	shapes[1][1].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.25 });
	shapes[1][2].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.25 });
	shapes[1][3].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.25 });

	shapes[2][0].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.25 });
	shapes[2][1].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.75 });
	shapes[2][2].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.75 });
	shapes[2][3].setPos(Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.75 });

	shapes[3][0].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.75 });
	shapes[3][1].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.75 });
	shapes[3][2].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.75 });
	shapes[3][3].setPos(Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.75 });
}
