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

enum TileType
{
	EMPTY,
	PLAYER,
	OBSTACLE,
	ITEM,
	MOVER,
	CHASER
};

enum Direction
{
	LEFTDIR,
	RIGHTDIR,
	UPDIR,
	DOWNDIR
};

struct Vec2
{
	double x;
	double y;
};

class Shape
{
public:
	Shape(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		:type(Type::NONE), color(255 - r,255 - g,255 -b), lineColor(r,g,b)
	{
		length = ws.GetCellLen() / 2;
	}
	Shape(Type drawType, unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		:type(drawType), color(255 - r, 255 - g, 255 - b), lineColor(r, g, b)
	{
		length = ws.GetCellLen() / 2;
	}

	Type getType() const { return type; }
	TileType getTileType() const { return tileType; }
	int getMoveType() const { return moveType; }
	Direction getDir() const { return dir.front(); };
	int getLength() const { return length; }
	POINT getChildPos() const { return childPos; }
	int getColor(int idx)
	{
		if (idx == 0) return color.r;
		else if (idx == 1) return color.g;
		else if (idx == 2) return color.b;
		else return 0;
	}

	void setType(Type _type) { type = _type; }
	void setTileType(TileType _type) { tileType = _type; }
	void setMoveType(int i) { moveType = i; }
	void setChild(POINT pos) { childExist = true; childPos = pos; }
	void setColor(int r, int g, int b) { color.r = r; color.g = g; color.b = b; }
	void setLineColor(int r, int g, int b) { lineColor.r = r; lineColor.g = g; lineColor.b = b; }
	
	void setShape(Type _type);
	void setShape(Type _type, int length);

	bool hasChild() { return childExist; }

	// 그리기
	void draw(HDC hDC, POINT pos) const;

	// 점 추가
	void addPoint(POINT point) { points.push_back(point); }

	// 모든 점 삭제
	void clear() { points.clear(); }
	
	// 색상 반전
	void invertColor();

	// dir 전용 함수들
	void push(Direction _dir) { dir.push(_dir); }
	void pop() { dir.pop(); }
	int dirSize() { return dir.size(); }

	friend void swap(Shape& first, Shape& second) noexcept {
		using std::swap;
		swap(first.dir, second.dir);
		swap(first.length, second.length);
		swap(first.color, second.color);
		swap(first.lineColor, second.lineColor);
		swap(first.type, second.type);
		swap(first.tileType, second.tileType);
		swap(first.points, second.points);
		swap(first.isDrawing, second.isDrawing);
		swap(first.isMoving, second.isMoving);
		swap(first.childExist, second.childExist);
		swap(first.childPos, second.childPos);
	}

private:
	std::queue<Direction> dir;	// 다음에 이동할 방향이 저장되어있는 큐

	int length = 0; // 도형의 반지름

	int moveType = 0;

	struct { unsigned int r, g, b; } color;		// 내부 색상
	struct { unsigned int r, g, b; } lineColor; // 테두리 색상

	Type type;	// 도형의 모양 종류
	TileType tileType = TileType::EMPTY;

	std::vector<POINT> points;  // 그려질 점들
	bool isDrawing = false;		// 그리는지 판단용
	bool isMoving = false;		// 움직이는지 판단용

	bool childExist = false;
	POINT childPos = POINT{ 0,0 };
};