#include "Shape.h"

void Shape::draw(HDC hDC, POINT pos) const
{
	if (type == Type::NONE) return;

	HPEN hPen = CreatePen(PS_SOLID, penWidth, colorPen);
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);

	HBRUSH hBrush = CreateSolidBrush(colorBrush);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	std::vector<POINT> p;
	p.reserve(points.size());
	for (int i{}; i < (int)points.size(); ++i)
	{
		p.push_back(POINT{ points[i].x + pos.x, points[i].y + pos.y});
	}

	switch (type)
	{
	case Type::TRIANGLE:case Type::RECTANGLE:case Type::POLYGON:
		Polygon(hDC, p.data(), (int)p.size());
		break;
	case Type::LINE:
		MoveToEx(hDC, p[0].x, p[0].y, NULL);
		LineTo(hDC, p[1].x, p[1].y);
		break;
	case Type::CIRCLE:
		Ellipse(hDC, p[0].x, p[0].y, p[1].x, p[1].y);
		break;
	case Type::STRING:
		TextOut(hDC, pos.x, pos.y, str.c_str(), str.size());
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
	type = _type;
	length = _length;

	switch (type)
	{
	case Type::CIRCLE:
		addPoint(POINT{ -_length,-_length });
		addPoint(POINT{ _length,_length });
		break;
	case Type::TRIANGLE:
		for (int i{}; i < 3; ++i)
		{
			int x = static_cast<int>(_length * cos(getRadian(i * 120.0f)));
			int y = static_cast<int>(_length * sin(getRadian(i * 120.0f)));

			addPoint(POINT{ x,y });
		}
		break;
	case Type::RECTANGLE:
		addPoint(POINT{ -_length, -_length });
		addPoint(POINT{ _length, -_length });
		addPoint(POINT{ _length,  _length });
		addPoint(POINT{ -_length,  _length });
		break;
	default:
		break;
	}
}

void Shape::setShape(Type _type, std::wstring _str)
{
	if (_type != Type::STRING) return;

	type = _type;
	str = _str;
	colorPen = RGB(255, 0, 0);
}

void Shape::clearAll()
{
	points.clear();
	length = 0;
	type = Type::NONE;
	colorPen = RGB(0, 0, 0);
	colorBrush = RGB(0, 0, 0);
}

void Shape::invertColor()
{
	colorBrush = RGB(255 - getColorBrush(0), 255 - getColorBrush(1), 255 - getColorBrush(2));
}