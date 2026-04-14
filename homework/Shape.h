#pragma once

#include "header.h"

extern SZ ws;

enum Type
{
	NONE,
	RECTANGLE,
	CIRCLE,
	TRIANGLE,
	POLYGON,
	LINE
};

enum Direction
{
	LEFTDIR,
	RIGHTDIR,
	UPDIR,
	DOWNDIR,
	STOP
};

class Shape
{
public:
	Shape(int _length = 10, unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		:type(Type::NONE), length(_length), colorPen(RGB(r,g,b)), colorBrush(RGB(255 - r, 255 - g, 255 - b))
	{
	}
	Shape(Type drawType, int _length = 10, unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		:type(drawType), length(_length), colorPen(RGB(r, g, b)), colorBrush(RGB(255 - r, 255 - g, 255 - b))
	{
		setShape(drawType, _length);
	}

	Type getType() const { return type; }
	int getLength() const { return length; }
	COLORREF getColorPen() const { return colorPen; }
	int getColorPen(int i) const
	{
		if (i == 0)
			return GetRValue(colorPen);
		else if (i == 1)
			return GetGValue(colorPen);
		else if (i == 2)
			return GetBValue(colorPen);
		else
			return 0;
	}
	COLORREF getColorBrush() const { return colorBrush; }
	int getColorBrush(int i) const
	{
		if (i == 0)
			return GetRValue(colorBrush);
		else if (i == 1)
			return GetGValue(colorBrush);
		else if (i == 2)
			return GetBValue(colorBrush);
		else
			return 0;
	}

	void setType(Type _type) { type = _type; }
	void setColorPen(COLORREF c) { colorPen = c; }
	void setColorBrush(COLORREF c) { colorBrush = c; }

	void setShape(Type _type);
	void setShape(Type _type, int length);

	// 그리기
	void draw(HDC hDC, POINT pos) const;

	// 점 추가
	void addPoint(POINT point) { points.push_back(point); }

	// 모든것을 백지로
	void clearAll();
	
	// 색상 반전
	void invertColor();

	friend void swap(Shape& first, Shape& second) noexcept {
		using std::swap;
		swap(first.length, second.length);
		swap(first.colorBrush, second.colorBrush);
		swap(first.colorPen, second.colorPen);
		swap(first.type, second.type);
		swap(first.points, second.points);
	}

private:
	int length = 0; // 도형의 반지름

	COLORREF colorBrush;// 내부 색상
	COLORREF colorPen;  // 테두리 색상

	Type type; // 도형의 타입(원,삼각형 등)

	std::vector<POINT> points;  // 그려질 점들
};