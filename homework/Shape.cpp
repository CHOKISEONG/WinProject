#include "Shape.h"

void Shape::setShape(Type type)
{
	switch (type)
	{
		
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
