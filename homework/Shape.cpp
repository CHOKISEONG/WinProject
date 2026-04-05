#include "Shape.h"

void Shape::setShape(Type _type, int length)
{
	clear();
	type = _type;

	switch (type)
	{
	case CIRCLE:
		addPoint(POINT{ -length,-length });
		addPoint(POINT{ length,length });
		break;
	case PIE:case CHORD: case ARC:
		addPoint(POINT{ -length,-length });
		addPoint(POINT{ length,length });
		addPoint(POINT{ 0,-length });
		addPoint(POINT{ -length, 0 });
		break;
	case TRIANGLE:
		for (int i{}; i < 3; ++i)
		{
			int x = length * cos(getRadian(i * 120.0f));
			int y = length * sin(getRadian(i * 120.0f));

			addPoint(POINT{ x,y });
		}
		break;
	case RECTANGLE:
		for (int i{}; i < 4; ++i)
		{
			int x = length * cos(getRadian(i * 90.0f));
			int y = length * sin(getRadian(i * 90.0f));

			addPoint(POINT{ x,y });
		}
		break;
	case PENTAGON:
		for (int i{}; i < 5; ++i)
		{
			int x = length * cos(getRadian(i * 72.0f));
			int y = length * sin(getRadian(i * 72.0f));

			addPoint(POINT{ x,y });
		}
		break;
	case HEXAGON:
		for (int i{}; i < 6; ++i)
		{
			int x = length * cos(getRadian(i * 60.0f));
			int y = length * sin(getRadian(i * 60.0f));

			addPoint(POINT{ x,y });
		}
		break;
	case STAR:
		for (int i{}; i < 10; ++i)
		{
			int x{};
			int y{};

			if (i % 2)
			{
				x = length/2 * cos(getRadian(i * 36.0f));
				y = length/2 * sin(getRadian(i * 36.0f));
			}
			else
			{
				x = length * cos(getRadian(i * 36.0f));
				y = length * sin(getRadian(i * 36.0f));
			}

			addPoint(POINT{ x,y });
		}
		break;
	default:
		break;
	}
}

void Shape::draw(HDC hDC) const
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);

	std::vector<POINT> p;
	for (int i{}; i < points.size(); ++i)
	{
		p.push_back(POINT{ points[i].x + pos.x, points[i].y + pos.y });
	}

	switch (this->type)
	{
	case POLY:case TRIANGLE:case RECTANGLE:case PENTAGON:case HEXAGON:case STAR:
		Polygon(hDC, p.data(), p.size());
		break;
	case CIRCLE:
		Ellipse(hDC, p[0].x, p[0].y, p[1].x, p[1].y);
		break;
	case ARC:
		Arc(hDC, p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y, p[3].x, p[3].y);
		break;
	case CHORD:
		Chord(hDC, p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y, p[3].x, p[3].y);
		break;
	case PIE:
		Pie(hDC, p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y, p[3].x, p[3].y);
		break;
	default:
		break;
	}

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);
}
