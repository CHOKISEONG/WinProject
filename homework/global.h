#pragma once

#include "header.h"

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }

// 윈도우의 가로, 세로 크기
class SZ
{
public:
	int WIDTH = 800;
	int HEIGHT = 600;

	int GetLength() const
	{
		return (WIDTH > HEIGHT) ? WIDTH / 12 : HEIGHT / 12;
	}
};
extern SZ ws;

// 색깔
struct Color { unsigned int r, g,  b; };

struct Shape
{
	POINT position;
	POINT* point;
	Color color, tmpColor;
	int pointNum;
	
	enum
	{
		Cirle,
		SandClock,
		Pentagon,
		Pie
	} type;
};

extern std::vector<Shape> shapes;
extern POINT positions[4];
extern Shape rect;
extern int midShapeIdx;

extern std::map<char, bool> isKeyDown;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;

// 함수 선언부
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void setPosition();
void drawPolygons(HDC hDC);
void drawMidShape(HDC hDC);
void makePolygons();
void shapeSwap(Shape& a, Shape& b);