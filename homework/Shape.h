#pragma once

#include "header.h"

enum Type
{
	NONE,
	RECTANGLE,
	CIRCLE,
	TRIANGLE
};

struct Vec2
{
	double x;
	double y;
};

inline int selectedShapes = -1;

class Shape
{
private:
	Vec2 pos;
	Vec2 dPos;

	std::vector<POINT> points;
	int length;

	struct{ unsigned int r, g, b; } color;

	Type type;

	long moveSpeed = 10.0f;
	Vec2 moveDir;

	float progress = 0.0f;
	int progressDir = 1;
public:
	bool isDrawing = false;
	bool isMoving = false;

	Shape(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		:type(Type::NONE), color(r,g,b)
	{
	}
	Shape(Type drawType, unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
		:type(drawType), color(r,g,b)
	{
	}

	void checkCollide();
	void draw(HDC hDC);
	void clear()
	{
		points.clear();
	}

	void setPos(Vec2 _pos) { pos = _pos; }
	void setType(Type _type) { type = _type; }
	void setColor(int r, int g, int b) { color.r = r; color.g = g; color.b = b; }
	void setDir(float degree);
	void setShape(Type _type, int length);
	

	Vec2 getPos() const { return pos; }
	Vec2 getPos(double degree);
	Type getType() const { return type;}
	float getProgress() const { return progress; }
	int getLength() const { return length; }
	

	void changeDir() { progressDir *= -1; }
	void updateProgress(float delta) { progress += delta * progressDir; }

	void addPoint(POINT point) { points.push_back(point); }

	void changeSpeed(float delta) { moveSpeed += delta; }
};

inline std::vector<std::vector<Shape>> shapes;


void shapeInitialize();
void selectShape(int idx);