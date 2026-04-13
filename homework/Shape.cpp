#include "Shape.h"

void Shape::checkCollide()
{
}

void Shape::draw(HDC hDC, POINT pos) const
{
	//if (type == Type::NONE || isDrawing == false) return;
	//else if (points.size() == 0) return;

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(lineColor.r, lineColor.g, lineColor.b));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	std::vector<POINT> p;
	p.reserve(points.size());
	for (int i{}; i < (int)points.size(); ++i)
	{
		p.push_back(POINT{ points[i].x + pos.x, points[i].y + pos.y});
	}

	switch (type)
	{
	case TRIANGLE:case RECTANGLE:case POLYGON:
		Polygon(hDC, p.data(), (int)p.size());
		break;
	case LINE:
		MoveToEx(hDC, p[0].x, p[0].y, NULL);
		LineTo(hDC, p[1].x, p[1].y);
		break;
	case CIRCLE:
		Ellipse(hDC, p[0].x, p[0].y, p[1].x, p[1].y);
		break;
	default:
		break;
	}

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
}

void Shape::setShape(Type _type)
{
	setShape(_type, length);
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
			int x = static_cast<int>(_length * cos(getRadian(i * 120.0f)));
			int y = static_cast<int>(_length * sin(getRadian(i * 120.0f)));

			addPoint(POINT{ x,y });
		}
		break;
	case RECTANGLE:
		addPoint(POINT{ -_length, -_length });
		addPoint(POINT{ _length, -_length });
		addPoint(POINT{ _length,  _length });
		addPoint(POINT{ -_length,  _length });
		break;
	default:
		break;
	}
}

void Shape::invertColor()
{
	color.r = 255 - color.r;
	color.g = 255 - color.g;
	color.b = 255 - color.b;

	lineColor.r = 255 - lineColor.r;
	lineColor.g = 255 - lineColor.g;
	lineColor.b = 255 - lineColor.b;
}