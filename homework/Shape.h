#pragma once

#include "header.h"

enum Type
{
	CIRCLE,
	PIE,
	ARC,
	CHORD,
	POLY,
	STAR,
	TRIANGLE,
	RECTANGLE,
	PENTAGON,
	HEXAGON
};

class Shape
{
private:
	POINT pos;

	std::vector<POINT> points;

	struct Color
	{
		unsigned int r, g, b;
	} color;

	Type type;
public:
	Shape(POINT _pos = POINT({ 0,0 }), unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		: pos(_pos), color(r,g,b), type(POLY)
	{
	}

	void setColor(int r, int g, int b) { color.r = r; color.g = g; color.b = b; }
	void setShape(Type type);

	void addPoint(POINT point){ points.push_back(point); }
	void clear() { points.clear(); }

	void draw(HDC hDC) const;
};

static std::vector<Shape> shapes;